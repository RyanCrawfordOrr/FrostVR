/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, Jan 2023
*/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UObject/NoExportTypes.h"
#include "Engine/LatentActionManager.h"

#include "EmbeddedVoiceChatChannel.h"
#include "EmbeddedVoiceChatAudioComponent.h"

#include "EmbeddedVoiceChatGroup.generated.h"

/**
**/
UCLASS(BlueprintType, meta=(BlueprintSpawnableComponent))
class EMBEDDEDVOICECHAT_API UEmbeddedVoiceChatGroup : public UActorComponent {
    GENERATED_BODY()

public:
    UEmbeddedVoiceChatGroup(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /** the channel handler class voice chat group will create when channel is assigned */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Embedded Voice Chat")
    TSubclassOf<UEmbeddedVoiceChatChannelHandler> channelHandlerClass = UEmbeddedVoiceChatChannelHandler::StaticClass();

    /**
    * please call before join any group
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    static void setIceServers(const TArray<FString> &iceServers, const int portRangeBegin, const int portRangeEnd);

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

    virtual bool GetComponentClassCanReplicate() const override;

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UFUNCTION(Server, Reliable, Category = "Embedded Voice Chat")
    void gotLocalDescription(UEmbeddedVoiceChatGroup* group, const EEmbeddedVoiceChatDescriptionType &descriptionType, const FString &description);

    UFUNCTION(Server, Reliable, Category = "Embedded Voice Chat")
    void gotLocalCandidate(UEmbeddedVoiceChatGroup* group, const FString &mid, const FString &candidate);

    UPROPERTY()
    UEmbeddedVoiceChatChannelHandler *channelHandler = nullptr;
    UPROPERTY()
    UEmbeddedVoiceChatChannel *channel = nullptr;

    /**
     * \param volume 0.0 means muted, 1.0 means normal
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    void setVolume(float volume);

    /**
     * \return 0.0 means muted, 1.0 means normal
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    float getVolume();

    float volume = 1.0f;

    /**
     * set 3d position of the speaker
     * \param location the location where the speaker is speaking
     * \param direction the direction where the speaker is facing. for doppler effect.
     * \param velocity the velocity of the speaker. for doppler effect.
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    void update3DPosition(const FVector &location, const FVector &direction, const FVector &velocity);

    /**
     * set 3d position of the player
     * \param location the location where the player is listening
     * \param direction the direction where the player is facing. for doppler effect.
     * \param velocity the velocity of the player. for doppler effect.
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    void updateListener3DPosition(const FVector &location, const FVector &direction, const FVector &velocity);

    /**
     * \return true if the channel has received voice package in the last isChannelTalkingThreshold milliseconds
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    bool isTalking();

    /**
     * \return a channel if the channel is valid or nullptr
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    UEmbeddedVoiceChatChannel *getChannel();

//    UPROPERTY()
//    UEmbeddedVoiceChatAudioComponent *audioComponent = nullptr;

    /**
     * bind output to audio component
     * because its audio will be redirected to an audio component. so, set its channel type to non position
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    void bindAudioComponent(UEmbeddedVoiceChatAudioComponent *tempAudioComponent);

    /**
     * get Sound wave to play in audio component
     * because its audio will be redirected to an audio component. so, set its channel type to non position
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
	UVoiceChatSoundWave *getSoundWave();

private:

    /**
    * join a group with the specified group name
    **/
    UFUNCTION(Server, Reliable, Category = "Embedded Voice Chat")
    void joinGroupServer(const FString &groupName);

    /**
     * leave a group with the specified group name
    **/
    UFUNCTION(Server, Reliable, Category = "Embedded Voice Chat")
    void leaveGroupServer(const FString &groupName);

    // Server only
    TArray<FString> groupNames;

    static TArray<UEmbeddedVoiceChatGroup *> groups;

    UFUNCTION(Client, Reliable, Category = "Embedded Voice Chat")
    void newPlayerJoin(UEmbeddedVoiceChatGroup *newPlayer);

    UFUNCTION(Client, Reliable, Category = "Embedded Voice Chat")
    void oldPlayerLeave(UEmbeddedVoiceChatGroup *newPlayer);

    UFUNCTION(Client, Reliable, Category = "Embedded Voice Chat")
    void gotRemoteDescription(UEmbeddedVoiceChatGroup* group, const EEmbeddedVoiceChatDescriptionType &descriptionType, const FString &description);

    UFUNCTION(Client, Reliable, Category = "Embedded Voice Chat")
    void gotRemoteCandidate(UEmbeddedVoiceChatGroup* group, const FString &mid, const FString &candidate);

    UPROPERTY()
    UEmbeddedVoiceChatConnectionHandler *connectionHandler = nullptr;

    UPROPERTY()
    UEmbeddedVoiceChatConnection *connection = nullptr;

    static TArray<FString> iceServers;

    static int portRangeBegin;

    static int portRangeEnd;

	UPROPERTY(Transient)
	TObjectPtr<UVoiceChatSoundWave> soundWave;
};

/**
 * the connection handler for group connection
 **/
UCLASS(Blueprintable)
class EMBEDDEDVOICECHAT_API UEmbeddedVoiceChatGroupConnectionHandler : public UEmbeddedVoiceChatConnectionHandler {
    GENERATED_BODY()

public:
    // handle errors
    void onStateChange_Implementation(const EEmbeddedVoiceChatConnectionState &state) override;

    void onLocalDescription_Implementation(const EEmbeddedVoiceChatDescriptionType &descriptionType, const FString &description) override;

    void onLocalCandidate_Implementation(const FString &mid, const FString &candidate) override;

    void onDataChannel_Implementation(const FString &channelId, const UEmbeddedVoiceChatChannel *channel) override;

    UPROPERTY()
    UEmbeddedVoiceChatGroup* fromPlayer;

    UPROPERTY()
    UEmbeddedVoiceChatGroup* toPlayer;
};
