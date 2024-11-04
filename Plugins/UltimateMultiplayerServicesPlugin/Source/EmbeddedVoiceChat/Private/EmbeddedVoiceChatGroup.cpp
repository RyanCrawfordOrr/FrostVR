/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, Jan 2023
 */

#include "EmbeddedVoiceChatGroup.h"

#include "EmbeddedVoiceChatGlobals.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Async/Async.h"
#include "Engine/World.h"

TArray<UEmbeddedVoiceChatGroup *> UEmbeddedVoiceChatGroup::groups = TArray<UEmbeddedVoiceChatGroup *>();

TArray<FString> UEmbeddedVoiceChatGroup::iceServers = TArray<FString>();
int UEmbeddedVoiceChatGroup::portRangeBegin = 0;
int UEmbeddedVoiceChatGroup::portRangeEnd = 0;

UEmbeddedVoiceChatGroup::UEmbeddedVoiceChatGroup(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/) : Super(ObjectInitializer) {
    SetIsReplicatedByDefault(true);
	SetAutoActivate(true);
}

void UEmbeddedVoiceChatGroup::joinGroup(const FString &groupName) {
    if (GetWorld()->GetNetMode() == NM_DedicatedServer) {
        LOG_EMBEDDEDVOICECHAT_WARNING("join group can only be called from client.");
        return;
    }

    if (iceServers.IsEmpty()) {
        LOG_EMBEDDEDVOICECHAT_WARNING("ice servers is not set.");
        return;
    }

    LOG_EMBEDDEDVOICECHAT_NORMAL(FString::Printf(TEXT("join group %s."), *groupName));

    this->joinGroupServer(groupName);
}

void UEmbeddedVoiceChatGroup::leaveGroup(const FString &groupName) {
    if (GetWorld()->GetNetMode() == NM_DedicatedServer) {
        LOG_EMBEDDEDVOICECHAT_WARNING("leave group can only be called from client.");
        return;
    }

    LOG_EMBEDDEDVOICECHAT_NORMAL(FString::Printf(TEXT("leave group %s."), *groupName));

    this->leaveGroupServer(groupName);
}

bool UEmbeddedVoiceChatGroup::GetComponentClassCanReplicate() const {
    return true;
}

void UEmbeddedVoiceChatGroup::joinGroupServer_Implementation(const FString &groupName) {
    if (groupNames.Contains(groupName)) {
        return;
    }

    LOG_EMBEDDEDVOICECHAT_NORMAL(FString::Printf(TEXT("join group server %s"), *groupName));

    groupNames.Add(groupName);

    for (const auto& group : groups) {
        if (group != this && group->groupNames.Contains(groupName)) {
            for (const auto& i : groupNames) {
                if (!i.Equals(groupName) && group->groupNames.Contains(i)) {
                    goto JoinGroupLoop;
                }
            }

            LOG_EMBEDDEDVOICECHAT_NORMAL(FString::Printf(TEXT("notify new player join")));
            group->newPlayerJoin(this);

JoinGroupLoop:;
        }
    }
}

void UEmbeddedVoiceChatGroup::leaveGroupServer_Implementation(const FString &groupName) {
    if (!groupNames.Contains(groupName)) {
        return;
    }

    LOG_EMBEDDEDVOICECHAT_NORMAL(FString::Printf(TEXT("leave group server %s"), *groupName));

    groupNames.Remove(groupName);

    for (const auto& group : groups) {
        if (group != this && group->groupNames.Contains(groupName)) {
            for (const auto& i : groupNames) {
                if (group->groupNames.Contains(i)) {
                    goto LeaveGroupLoop;
                }
            }

            LOG_EMBEDDEDVOICECHAT_NORMAL(FString::Printf(TEXT("notify old player leave")));
            group->oldPlayerLeave(this);

LeaveGroupLoop:;
        }
    }
}

void UEmbeddedVoiceChatGroup::newPlayerJoin_Implementation(UEmbeddedVoiceChatGroup *newPlayer) {
    if (newPlayer->iceServers.IsEmpty()) {
        LOG_EMBEDDEDVOICECHAT_WARNING("new player's ice servers is not set.");
        return;
    }

    if (newPlayer == nullptr) {
        LOG_EMBEDDEDVOICECHAT_WARNING("new player is null. please check if the group component is replicated or not. ");
        return;
    }

    LOG_EMBEDDEDVOICECHAT_NORMAL(FString::Printf(TEXT("new player joined")));

	if (newPlayer->channel) {
		if (newPlayer->channel->IsRooted()) {
			newPlayer->channel->RemoveFromRoot();
		}
	}

	if (newPlayer->channelHandler) {
		if (newPlayer->channelHandler->IsRooted()) {
			newPlayer->channelHandler->RemoveFromRoot();
		}
	}

	if (newPlayer->connection) {
		if (newPlayer->connection->IsRooted()) {
			newPlayer->connection->RemoveFromRoot();
		}
	}

	if (newPlayer->connectionHandler) {
		if (newPlayer->connectionHandler->IsRooted()) {
			newPlayer->connectionHandler->RemoveFromRoot();
		}
	}

    newPlayer->connection = UEmbeddedVoiceChatConnection::createConnection();
    UEmbeddedVoiceChatGroupConnectionHandler* groupConnectionHandler = NewObject<UEmbeddedVoiceChatGroupConnectionHandler>();
    groupConnectionHandler->fromPlayer = this;
    groupConnectionHandler->toPlayer = newPlayer;
    newPlayer->connectionHandler = groupConnectionHandler;
    newPlayer->connection->registerConnectionHandler(newPlayer->connectionHandler);
    newPlayer->connection->connect(UEmbeddedVoiceChatGroup::iceServers, UEmbeddedVoiceChatGroup::portRangeBegin, UEmbeddedVoiceChatGroup::portRangeEnd);
    FEmbeddedVoiceChatChannelId channelId;
    channelId.id = FString::Printf(TEXT("%d_%d"), newPlayer->GetUniqueID(), this->GetUniqueID());
    newPlayer->channel = newPlayer->connection->createChannel(channelId);
	newPlayer->channel->AddToRoot();
    if (UKismetSystemLibrary::IsValidClass(newPlayer->channelHandlerClass)) {
        newPlayer->channelHandler = NewObject<UEmbeddedVoiceChatChannelHandler>(newPlayer, newPlayer->channelHandlerClass);
        newPlayer->channel->registerChannelHandler(newPlayer->channelHandler);
//		newPlayer->channelHandler->AddToRoot();
    }
    newPlayer->channel->setVolume(newPlayer->volume);
	newPlayer->connection->AddToRoot();
	newPlayer->connectionHandler->AddToRoot();
}

void UEmbeddedVoiceChatGroup::oldPlayerLeave_Implementation(UEmbeddedVoiceChatGroup *newPlayer) {

    LOG_EMBEDDEDVOICECHAT_NORMAL(FString::Printf(TEXT("old player left")));

    if (newPlayer->channel) {
        newPlayer->channel->close();

		if (newPlayer->channel->IsRooted()) {
			newPlayer->channel->RemoveFromRoot();
		}

        newPlayer->channel = nullptr;
    }

	if (newPlayer->channelHandler) {
		if (newPlayer->channelHandler->IsRooted()) {
			newPlayer->channelHandler->RemoveFromRoot();
		}
	}

    if (newPlayer->connection) {
        newPlayer->connection->close();

	    if (newPlayer->connection->IsRooted()) {
		    newPlayer->connection->RemoveFromRoot();
	    }

        newPlayer->connection = nullptr;
    }

	if (newPlayer->connectionHandler) {
		if (newPlayer->connectionHandler->IsRooted()) {
			newPlayer->connectionHandler->RemoveFromRoot();
		}
	}
}

void UEmbeddedVoiceChatGroup::gotLocalDescription_Implementation(UEmbeddedVoiceChatGroup* group, const EEmbeddedVoiceChatDescriptionType &descriptionType, const FString &description) {
    group->gotRemoteDescription(this, descriptionType, description);
}

void UEmbeddedVoiceChatGroup::gotRemoteDescription_Implementation(UEmbeddedVoiceChatGroup* group, const EEmbeddedVoiceChatDescriptionType &descriptionType, const FString &description) {
    if (group == nullptr) {
        LOG_EMBEDDEDVOICECHAT_WARNING("got remote description but group is not valid.");
        return;
    }

    if (descriptionType == EEmbeddedVoiceChatDescriptionType::Offer) {
        if (group->connection == nullptr) {
	        LOG_EMBEDDEDVOICECHAT_NORMAL(FString::Printf(TEXT("got offer description")));

	        if (group->connectionHandler) {
		        if (group->connectionHandler->IsRooted()) {
			        group->connectionHandler->RemoveFromRoot();
		        }
	        }

            group->connection = UEmbeddedVoiceChatConnection::createConnection();
            UEmbeddedVoiceChatGroupConnectionHandler* groupConnectionHandler = NewObject<UEmbeddedVoiceChatGroupConnectionHandler>();
            groupConnectionHandler->fromPlayer = this;
            groupConnectionHandler->toPlayer = group;
            group->connectionHandler = groupConnectionHandler;
            group->connection->registerConnectionHandler(group->connectionHandler);
            group->connection->connect(UEmbeddedVoiceChatGroup::iceServers, UEmbeddedVoiceChatGroup::portRangeBegin, UEmbeddedVoiceChatGroup::portRangeEnd);
	        group->connection->AddToRoot();
	        group->connectionHandler->AddToRoot();
        } else {
			return;
		}
    }

    if (group->connection == nullptr) {
        LOG_EMBEDDEDVOICECHAT_WARNING("got remote description but connection is nullptr.");
        return;
    }

    group->connection->setRemoteDescription(descriptionType, description);
}

void UEmbeddedVoiceChatGroup::gotLocalCandidate_Implementation(UEmbeddedVoiceChatGroup* group, const FString &mid, const FString &candidate) {
    group->gotRemoteCandidate(this, mid, candidate);
}

void UEmbeddedVoiceChatGroup::gotRemoteCandidate_Implementation(UEmbeddedVoiceChatGroup* group, const FString &mid, const FString &candidate) {
    if (group == nullptr || group->connection == nullptr) {
        LOG_EMBEDDEDVOICECHAT_WARNING("got remote candidate but connection is nullptr.");
        return;
    }

    group->connection->addRemoteCandidate(mid, candidate);
}

void UEmbeddedVoiceChatGroup::setVolume(float tempVolume) {
    if (this->channel == nullptr) {
        this->volume = tempVolume;
        return;
    }

    this->volume = tempVolume;
    this->channel->setVolume(volume);
}

float UEmbeddedVoiceChatGroup::getVolume() {
    if (this->channel == nullptr) {
        return volume;
    }

    return this->channel->getVolume();
}

void UEmbeddedVoiceChatGroup::update3DPosition(const FVector &location, const FVector &direction, const FVector &velocity) {
    if (this->channel == nullptr) {
        LOG_EMBEDDEDVOICECHAT_WARNING("update 3D position but channel is nullptr.");
        return;
    }

    return this->channel->update3DPosition(location, direction, velocity);
}

void UEmbeddedVoiceChatGroup::updateListener3DPosition(const FVector &location, const FVector &direction, const FVector &velocity) {
    if (this->channel == nullptr) {
        LOG_EMBEDDEDVOICECHAT_WARNING("update listener 3D position but channel is nullptr.");
        return;
    }

    return this->channel->updateListener3DPosition(location, direction, velocity);
}

bool UEmbeddedVoiceChatGroup::isTalking() {
    if (this->channel == nullptr) {
        return false;
    }

    return this->channel->isTalking();
}

UEmbeddedVoiceChatChannel *UEmbeddedVoiceChatGroup::getChannel() {
    return this->channel;
}

void UEmbeddedVoiceChatGroup::bindAudioComponent(UEmbeddedVoiceChatAudioComponent *tempAudioComponent) {
	if (tempAudioComponent == nullptr) {
		return;
	}

#if WITH_EMBEDDEDVOICECHAT
	this->channel->EmbeddedVoiceChatChannel->clearCache();
#endif

	tempAudioComponent->setGroup(this);
}

UVoiceChatSoundWave *UEmbeddedVoiceChatGroup::getSoundWave() {
	if (!soundWave) {
		soundWave = NewObject<UVoiceChatSoundWave>();

#if WITH_EMBEDDEDVOICECHAT
		this->channel->EmbeddedVoiceChatChannel->clearCache();
#endif

		soundWave->Init(this);
	}

	return soundWave;
}

void UEmbeddedVoiceChatGroup::BeginPlay() {
    Super::BeginPlay();

    LOG_EMBEDDEDVOICECHAT_NORMAL(FString::Printf(TEXT("a group component is calling begin play. ")));

    UEmbeddedVoiceChatGroup::groups.Add(this);
}

void UEmbeddedVoiceChatGroup::EndPlay(const EEndPlayReason::Type EndPlayReason) {
    Super::EndPlay(EndPlayReason);

    LOG_EMBEDDEDVOICECHAT_NORMAL(FString::Printf(TEXT("a group component is calling end play. ")));

	if (this->channel) {
		if (this->channel->IsRooted()) {
			this->channel->RemoveFromRoot();
		}
	}

	if (this->channelHandler) {
		if (this->channelHandler->IsRooted()) {
			this->channelHandler->RemoveFromRoot();
		}
	}

	if (this->connection) {
		if (this->connection->IsRooted()) {
			this->connection->RemoveFromRoot();
		}
	}

	if (this->connectionHandler) {
		if (this->connectionHandler->IsRooted()) {
			this->connectionHandler->RemoveFromRoot();
		}
	}

    UEmbeddedVoiceChatGroup::groups.Remove(this);

    if (GetWorld()->GetNetMode() == NM_DedicatedServer) {
        return;
    }
}

void UEmbeddedVoiceChatGroupConnectionHandler::onStateChange_Implementation(const EEmbeddedVoiceChatConnectionState &state) {
//    @TODO: handle failure
    switch (state) {
        case EEmbeddedVoiceChatConnectionState::Disconnected:
        case EEmbeddedVoiceChatConnectionState::Failed:
        case EEmbeddedVoiceChatConnectionState::Closed:
            break;
    }
}

void UEmbeddedVoiceChatGroupConnectionHandler::onLocalDescription_Implementation(const EEmbeddedVoiceChatDescriptionType &descriptionType, const FString &description) {
    AsyncTask(ENamedThreads::GameThread, [this, descriptionType, description]{
        fromPlayer->gotLocalDescription(toPlayer, descriptionType, description);
    });
}

void UEmbeddedVoiceChatGroupConnectionHandler::onLocalCandidate_Implementation(const FString &mid, const FString &candidate) {
    AsyncTask(ENamedThreads::GameThread, [this, mid, candidate]{
        fromPlayer->gotLocalCandidate(toPlayer, mid, candidate);
    });
}

void UEmbeddedVoiceChatGroupConnectionHandler::onDataChannel_Implementation(const FString &channelId, const UEmbeddedVoiceChatChannel *channel) {

	LOG_EMBEDDEDVOICECHAT_NORMAL(FString::Printf(TEXT("got data channel")));

	if (toPlayer->channel) {
		if (toPlayer->channel->IsRooted()) {
			toPlayer->channel->RemoveFromRoot();
		}
	}

	if (toPlayer->channelHandler) {
		if (toPlayer->channelHandler->IsRooted()) {
			toPlayer->channelHandler->RemoveFromRoot();
		}
	}

    toPlayer->channel = (UEmbeddedVoiceChatChannel *)channel;
	toPlayer->channel->AddToRoot();
    if (UKismetSystemLibrary::IsValidClass(toPlayer->channelHandlerClass)) {
        toPlayer->channelHandler = NewObject<UEmbeddedVoiceChatChannelHandler>(toPlayer, toPlayer->channelHandlerClass);
        toPlayer->channel->registerChannelHandler(toPlayer->channelHandler);
//		toPlayer->channelHandler->AddToRoot();
    }
    toPlayer->channel->setVolume(toPlayer->volume);
}

void UEmbeddedVoiceChatGroup::setIceServers(const TArray<FString> &tempIceServers, const int tempPortRangeBegin, const int tempPortRangeEnd) {
    UEmbeddedVoiceChatGroup::iceServers = tempIceServers;
    UEmbeddedVoiceChatGroup::portRangeBegin = tempPortRangeBegin;
    UEmbeddedVoiceChatGroup::portRangeEnd = tempPortRangeEnd;
}