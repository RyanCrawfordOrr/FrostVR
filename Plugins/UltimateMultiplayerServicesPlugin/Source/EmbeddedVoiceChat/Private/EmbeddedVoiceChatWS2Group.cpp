/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, May 2024
 */

#include "EmbeddedVoiceChatWS2Group.h"
#include "EmbeddedVoiceChatGlobals.h"
#include "EmbeddedVoiceChatPrivatePCH.h"

#if WITH_EMBEDDEDVOICECHAT

#include "EmbeddedVoiceChat/EmbeddedVoiceChatCommon.h"

#endif

#include "Engine/Engine.h"
#include "LatentActions.h"

UEmbeddedVoiceChatWS2Group::UEmbeddedVoiceChatWS2Group(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/) : Super(ObjectInitializer) {
}

void UEmbeddedVoiceChatWS2Group::BeginDestroy() {
	Super::BeginDestroy();
#if WITH_EMBEDDEDVOICECHAT
	if (this->EmbeddedVoiceChatWS2Group) {
		this->EmbeddedVoiceChatWS2Group->disconnectWSServer();
	}
#endif
}

bool UEmbeddedVoiceChatWS2Group::IsReadyForFinishDestroy() {
#if WITH_EMBEDDEDVOICECHAT
	if (this->EmbeddedVoiceChatWS2Group) {
		return !this->EmbeddedVoiceChatWS2Group->isWSServerConnected();
	}
#endif
	return true;
}

void UEmbeddedVoiceChatWS2Group::setPlayerId(const FString &playerId) {
#if WITH_EMBEDDEDVOICECHAT
	this->EmbeddedVoiceChatWS2Group = EmbeddedVoiceChat::WSGroup2::create(TCHAR_TO_UTF8(*playerId));
#endif
}

void UEmbeddedVoiceChatWS2Group::setIceServers(const TArray<FString> &iceServers, const int portRangeBegin, const int portRangeEnd) {
#if WITH_EMBEDDEDVOICECHAT
	if (this->EmbeddedVoiceChatWS2Group) {
		std::vector<std::string> servers;
		for (const auto& elem : iceServers) {
			servers.emplace_back(TCHAR_TO_UTF8(*elem));
		}
		this->EmbeddedVoiceChatWS2Group->setIceServers(servers, portRangeBegin, portRangeEnd);
	}
#endif
}

void UEmbeddedVoiceChatWS2Group::connectWSServer(const FString &wsServerURL, const TMap<FString, FString> &queryParameters, const TMap<FString, FString> &headers) {
#if WITH_EMBEDDEDVOICECHAT
	if (this->EmbeddedVoiceChatWS2Group) {
		std::map<std::string, std::string> EmbeddedVoiceChatWSServerQueryParameters;
		std::map<std::string, std::string> EmbeddedVoiceChatWSServerHeaders;

		for (const auto &queryParameter : queryParameters) {
			EmbeddedVoiceChatWSServerQueryParameters.insert(std::pair<std::string, std::string>(TCHAR_TO_UTF8(*queryParameter.Key), TCHAR_TO_UTF8(*queryParameter.Value)));
		}

		for (const auto &header : headers) {
			EmbeddedVoiceChatWSServerHeaders.insert(std::pair<std::string, std::string>(TCHAR_TO_UTF8(*header.Key), TCHAR_TO_UTF8(*header.Value)));
		}

		this->EmbeddedVoiceChatWS2Group->connectWSServer(TCHAR_TO_UTF8(*wsServerURL), EmbeddedVoiceChatWSServerQueryParameters, EmbeddedVoiceChatWSServerHeaders);
	}
#endif
}

UEmbeddedVoiceChatChannel * UEmbeddedVoiceChatWS2Group::getChannel(const FString &playerId) {
	UEmbeddedVoiceChatChannel * channel = nullptr;
#if WITH_EMBEDDEDVOICECHAT
	if (this->EmbeddedVoiceChatWS2Group) {
		std::shared_ptr<EmbeddedVoiceChat::Channel> embeddedVoiceChatChannel = this->EmbeddedVoiceChatWS2Group->getChannel(TCHAR_TO_UTF8(*playerId));
		if (embeddedVoiceChatChannel) {
			channel = NewObject<UEmbeddedVoiceChatChannel>();
			channel->EmbeddedVoiceChatChannel = embeddedVoiceChatChannel;
		}
	}
#endif
	return channel;
}

#if WITH_EMBEDDEDVOICECHAT
class FWS2GetGroupSizeAction : public FPendingLatentAction {
private:
	std::shared_ptr<EmbeddedVoiceChat::WSGroup2> EmbeddedVoiceChatWS2Group;

	int &size;
	bool completed = false;

	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;

public:
	FWS2GetGroupSizeAction(
			struct FLatentActionInfo LatentInfo,
			std::shared_ptr<EmbeddedVoiceChat::WSGroup2> EmbeddedVoiceChatWS2Group,
			int &size,
			const FString &groupName = TEXT("Default")
	) :
			EmbeddedVoiceChatWS2Group(EmbeddedVoiceChatWS2Group),
			size(size),
			ExecutionFunction(LatentInfo.ExecutionFunction),
	OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {
		if (EmbeddedVoiceChatWS2Group) {
			EmbeddedVoiceChatWS2Group->countGroup(TCHAR_TO_UTF8(*groupName), [this](int const &count) {
				this->completed = true;
				this->size = count;
			});
		} else {
			completed = true;
		}
	}

	void UpdateOperation(FLatentResponse &Response) override {
		Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
	}

#if WITH_EDITOR

	// Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("Get Token");
    }

#endif
};
#endif

void
UEmbeddedVoiceChatWS2Group::getGroupSize(
		UObject *WorldContextObject,
		struct FLatentActionInfo LatentInfo,
		int &size,
		const FString &groupName
) {
#if WITH_EMBEDDEDVOICECHAT
	// Prepare latent action
	if (this->EmbeddedVoiceChatWS2Group) {
		if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
			FLatentActionManager & LatentActionManager = World->GetLatentActionManager();
			if (LatentActionManager.FindExistingAction<FWS2GetGroupSizeAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
				LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
				                                 new FWS2GetGroupSizeAction(
						                                 LatentInfo,
														 this->EmbeddedVoiceChatWS2Group,
						                                 size,
						                                 groupName
				                                 )
				);
			}
		}
	}
	return;
#endif
}

void UEmbeddedVoiceChatWS2Group::bindAudioComponent(UEmbeddedVoiceChatWS2AudioComponent *tempAudioComponent, const FString &playerId) {
	if (tempAudioComponent == nullptr) {
		return;
	}

#if WITH_EMBEDDEDVOICECHAT
	this->EmbeddedVoiceChatWS2Group->getChannel(TCHAR_TO_UTF8(*playerId))->clearCache();
#endif

	tempAudioComponent->setGroup(this, playerId);
}

UVoiceChatWS2SoundWave *UEmbeddedVoiceChatWS2Group::getSoundWave(const FString &playerId) {
	if (!soundWave) {
		soundWave = NewObject<UVoiceChatWS2SoundWave>();

#if WITH_EMBEDDEDVOICECHAT
		this->EmbeddedVoiceChatWS2Group->getChannel(TCHAR_TO_UTF8(*playerId))->clearCache();
#endif

		soundWave->Init(this, playerId);
	}

	return soundWave;
}

void UEmbeddedVoiceChatWS2Group::joinGroup(const FString &groupName) {
#if WITH_EMBEDDEDVOICECHAT
	if (this->EmbeddedVoiceChatWS2Group) {
		this->EmbeddedVoiceChatWS2Group->joinGroup(TCHAR_TO_UTF8(*groupName));
	}
#endif
}

void UEmbeddedVoiceChatWS2Group::leaveGroup(const FString &groupName) {
#if WITH_EMBEDDEDVOICECHAT
	if (this->EmbeddedVoiceChatWS2Group) {
		this->EmbeddedVoiceChatWS2Group->leaveGroup(TCHAR_TO_UTF8(*groupName));
	}
#endif
}