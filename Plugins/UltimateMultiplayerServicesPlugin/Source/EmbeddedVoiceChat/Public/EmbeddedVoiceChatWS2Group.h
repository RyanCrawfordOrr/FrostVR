/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, May 2024
*/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/LatentActionManager.h"
#include "Components/SynthComponent.h"
#include "Sound/SoundGenerator.h"
#include "AudioResampler.h"

#if WITH_EMBEDDEDVOICECHAT

#include "EmbeddedVoiceChat/EmbeddedVoiceChatWSGroup.h"

#endif

#include "EmbeddedVoiceChatChannel.h"
#include "EmbeddedVoiceChatWS2AudioComponent.h"

#include "EmbeddedVoiceChatWS2Group.generated.h"

/**
**/
UCLASS(BlueprintType, meta=(BlueprintSpawnableComponent))
class EMBEDDEDVOICECHAT_API UEmbeddedVoiceChatWS2Group : public UActorComponent {
    GENERATED_BODY()

public:
#if WITH_EMBEDDEDVOICECHAT
	std::shared_ptr<EmbeddedVoiceChat::WSGroup2> EmbeddedVoiceChatWS2Group;
#endif
	UEmbeddedVoiceChatWS2Group(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginDestroy() override;
	virtual bool IsReadyForFinishDestroy() override;

	/**
	* please call before call any other functions
	**/
	UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
	void setPlayerId(const FString &playerId = TEXT("123"));

	/**
	* please call before join any group
	**/
	UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
	void setIceServers(const TArray<FString> &iceServers, const int portRangeBegin, const int portRangeEnd);

	/**
	* please call before join any group
	**/
	UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
	void connectWSServer(const FString &wsServerURL, const TMap<FString, FString> &queryParameters, const TMap<FString, FString> &headers);

	/**
	* get channel by player id
	**/
	UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
	UEmbeddedVoiceChatChannel * getChannel(const FString &playerId = TEXT("123"));

	/**
	* get number of player in a group
	**/
	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "Embedded Voice Chat")
	void getGroupSize (
			UObject *WorldContextObject,
			struct FLatentActionInfo LatentInfo,
			int &size,
			const FString &groupName = TEXT("Default")
	);

	/**
	* join a group with the specified group name
	**/
	UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
	void joinGroup(const FString &groupName = TEXT("Default"));

	/**
	 * leave a group with the specified group name
	**/
	UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
	void leaveGroup(const FString &groupName = TEXT("Default"));

	/**
	 * bind output to audio component
	 * because its audio will be redirected to an audio component. so, set its channel type to non position
	**/
	UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
	void bindAudioComponent(UEmbeddedVoiceChatWS2AudioComponent *tempAudioComponent, const FString &playerId);

	/**
	 * get Sound wave to play in audio component
	 * because its audio will be redirected to an audio component. so, set its channel type to non position
	**/
	UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
	UVoiceChatWS2SoundWave *getSoundWave(const FString &playerId);

	UPROPERTY(Transient)
	TObjectPtr<UVoiceChatWS2SoundWave> soundWave;
};
