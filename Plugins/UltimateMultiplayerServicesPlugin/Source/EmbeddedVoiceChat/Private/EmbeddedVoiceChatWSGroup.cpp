/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, Jan 2023
 */

#include "EmbeddedVoiceChatWSGroup.h"
#include "EmbeddedVoiceChatGlobals.h"
#include "EmbeddedVoiceChatPrivatePCH.h"

#if WITH_EMBEDDEDVOICECHAT

#include "EmbeddedVoiceChat/EmbeddedVoiceChatCommon.h"

#endif

#include "Engine/Engine.h"
#include "LatentActions.h"

UEmbeddedVoiceChatWSGroup::UEmbeddedVoiceChatWSGroup(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/) : Super(ObjectInitializer) {
#if WITH_EMBEDDEDVOICECHAT
	EmbeddedVoiceChatWSGroup = EmbeddedVoiceChat::WSGroup::create();
    this->EmbeddedVoiceChatDevice = std::make_shared<EmbeddedVoiceChat::AbstractPlaybackDevice>();

    NumChannels = EmbeddedVoiceChat::outputChannelCount;
#endif
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.SetTickFunctionEnable(true);

	SetComponentTickEnabled(true);
	SetComponentTickInterval(0.1);
	SetAutoActivate(true);
	bIsUISound = true;
}

void UEmbeddedVoiceChatWSGroup::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
#if WITH_EMBEDDEDVOICECHAT
	// update position. TransformUpdated
	FVector location = this->GetComponentLocation();
	float embeddedVoiceChatLocation[3] = {location.X, location.Y, location.Z};
	FVector forward = this->GetForwardVector();
	float embeddedVoiceChatDirection[3] = {forward.X, forward.Y, forward.Z};
	FVector velocity = this->GetComponentVelocity();
	float embeddedVoiceChatVelocity[3] = {velocity.X, velocity.Y, velocity.Z};
	EmbeddedVoiceChat::updateListener3DPosition(embeddedVoiceChatLocation, embeddedVoiceChatDirection, embeddedVoiceChatVelocity);
#endif
}

void UEmbeddedVoiceChatWSGroup::BeginDestroy() {
	Super::BeginDestroy();
#if WITH_EMBEDDEDVOICECHAT
	if (this->EmbeddedVoiceChatWSGroup) {
		this->EmbeddedVoiceChatWSGroup->disconnectWSServer();
	}
#endif
}

bool UEmbeddedVoiceChatWSGroup::IsReadyForFinishDestroy() {
#if WITH_EMBEDDEDVOICECHAT
	if (this->EmbeddedVoiceChatWSGroup) {
		return !this->EmbeddedVoiceChatWSGroup->isWSServerConnected();
	}
#endif
	return true;
}

void UEmbeddedVoiceChatWSGroup::setIceServers(const TArray<FString> &iceServers, const int portRangeBegin, const int portRangeEnd) {
#if WITH_EMBEDDEDVOICECHAT
	if (this->EmbeddedVoiceChatWSGroup) {
		std::vector<std::string> servers;
		for (const auto& elem : iceServers) {
			servers.emplace_back(TCHAR_TO_UTF8(*elem));
		}
		this->EmbeddedVoiceChatWSGroup->setIceServers(servers, portRangeBegin, portRangeEnd);
	}
#endif
}

void UEmbeddedVoiceChatWSGroup::connectWSServer(const FString &wsServerURL, const TMap<FString, FString> &queryParameters, const TMap<FString, FString> &headers) {
#if WITH_EMBEDDEDVOICECHAT
	if (this->EmbeddedVoiceChatWSGroup) {
		std::map<std::string, std::string> EmbeddedVoiceChatWSServerQueryParameters;
		std::map<std::string, std::string> EmbeddedVoiceChatWSServerHeaders;

		for (const auto &queryParameter : queryParameters) {
			EmbeddedVoiceChatWSServerQueryParameters.insert(std::pair<std::string, std::string>(TCHAR_TO_UTF8(*queryParameter.Key), TCHAR_TO_UTF8(*queryParameter.Value)));
		}

		for (const auto &header : headers) {
			EmbeddedVoiceChatWSServerHeaders.insert(std::pair<std::string, std::string>(TCHAR_TO_UTF8(*header.Key), TCHAR_TO_UTF8(*header.Value)));
		}

		this->EmbeddedVoiceChatWSGroup->connectWSServer(TCHAR_TO_UTF8(*wsServerURL), EmbeddedVoiceChatWSServerQueryParameters, EmbeddedVoiceChatWSServerHeaders);
	}
#endif
}

TArray<UEmbeddedVoiceChatChannel *> UEmbeddedVoiceChatWSGroup::getChannels() {
	TArray<UEmbeddedVoiceChatChannel *> channels;
#if WITH_EMBEDDEDVOICECHAT
	if (this->EmbeddedVoiceChatWSGroup) {
		std::vector<std::shared_ptr<EmbeddedVoiceChat::Channel>> embeddedVoiceChatChannels = this->EmbeddedVoiceChatWSGroup->getChannels();
		for (auto &embeddedVoiceChatChannel : embeddedVoiceChatChannels) {
			UEmbeddedVoiceChatChannel *channel = NewObject<UEmbeddedVoiceChatChannel>();
	        channel->EmbeddedVoiceChatChannel = embeddedVoiceChatChannel;
			channels.Add(channel);
		}
	}
#endif
	return channels;
}

#if WITH_EMBEDDEDVOICECHAT
class FWSGetGroupSizeAction : public FPendingLatentAction {
private:
	std::shared_ptr<EmbeddedVoiceChat::WSGroup> EmbeddedVoiceChatWSGroup;

	int &size;
	bool completed = false;

	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;

public:
	FWSGetGroupSizeAction(
			struct FLatentActionInfo LatentInfo,
			std::shared_ptr<EmbeddedVoiceChat::WSGroup> EmbeddedVoiceChatWSGroup,
			int &size,
			const FString &groupName = TEXT("Default")
	) :
			EmbeddedVoiceChatWSGroup(EmbeddedVoiceChatWSGroup),
			size(size),
			ExecutionFunction(LatentInfo.ExecutionFunction),
			OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {
		if (EmbeddedVoiceChatWSGroup) {
			EmbeddedVoiceChatWSGroup->countGroup(TCHAR_TO_UTF8(*groupName), [this](int const &count) {
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
UEmbeddedVoiceChatWSGroup::getGroupSize(
		UObject *WorldContextObject,
		struct FLatentActionInfo LatentInfo,
		int &size,
		const FString &groupName
) {
#if WITH_EMBEDDEDVOICECHAT
	// Prepare latent action
	if (this->EmbeddedVoiceChatWSGroup) {
		if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
			FLatentActionManager & LatentActionManager = World->GetLatentActionManager();
			if (LatentActionManager.FindExistingAction<FWSGetGroupSizeAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
				LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
				                                 new FWSGetGroupSizeAction(
						                                 LatentInfo,
														 this->EmbeddedVoiceChatWSGroup,
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

void UEmbeddedVoiceChatWSGroup::joinGroup(const FString &groupName) {
#if WITH_EMBEDDEDVOICECHAT
	if (this->EmbeddedVoiceChatWSGroup) {
		this->EmbeddedVoiceChatWSGroup->joinGroup(TCHAR_TO_UTF8(*groupName));
	}
#endif
}

void UEmbeddedVoiceChatWSGroup::leaveGroup(const FString &groupName) {
#if WITH_EMBEDDEDVOICECHAT
	if (this->EmbeddedVoiceChatWSGroup) {
		this->EmbeddedVoiceChatWSGroup->leaveGroup(TCHAR_TO_UTF8(*groupName));
	}
#endif
}

int32 UEmbeddedVoiceChatWSGroup::OnGenerateAudio(float* OutAudio, int32 NumSamples) {
#if WITH_EMBEDDEDVOICECHAT
	if (!(this->EmbeddedVoiceChatWSGroup)) {
        LOG_EMBEDDEDVOICECHAT_WARNING(FString::Printf(TEXT("ws group is not created correctly or may be destroyed")));
        return 0;
    }

	if (!(this->EmbeddedVoiceChatDevice)) {
        LOG_EMBEDDEDVOICECHAT_WARNING(FString::Printf(TEXT("device is not created correctly or may be destroyed")));
        return 0;
    }

    std::vector<float> cache;

    cache.reserve(NumSamples);
    this->EmbeddedVoiceChatDevice->getRenderedAudio(cache, NumSamples / NumChannels);

    LOG_EMBEDDEDVOICECHAT_VERYVERBOSE(FString::Printf(TEXT("got cached %d samples and %d channels"), NumSamples, NumChannels));

    for (int i = 0; i < NumSamples; i++) {
        if (i < cache.size() && !EmbeddedVoiceChat::deafened) {
            OutAudio[i] = FMath::Clamp<float>(cache[i] * VolumeMultiplier, -1.0, 1.0);
        } else {
            OutAudio[i] = 0;
        }
    }

    return NumSamples;
#endif
	return 0;
}

bool UEmbeddedVoiceChatWSGroup::Init(int32& SampleRate) {
#if WITH_EMBEDDEDVOICECHAT
	SampleRate = EmbeddedVoiceChat::sampleRate;
#endif
	return true;
}