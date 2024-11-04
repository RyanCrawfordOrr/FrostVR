/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, Feb 2022
*/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/LatentActionManager.h"
#include "Math/Vector.h"

#if WITH_EMBEDDEDVOICECHAT

#include "EmbeddedVoiceChat/EmbeddedVoiceChatChannel.h"

#endif

#include "EmbeddedVoiceChatChannelId.h"
#include "EmbeddedVoiceChatChannel3DProperties.h"

#include "EmbeddedVoiceChatChannel.generated.h"

UENUM(BlueprintType)
enum class EEmbeddedVoiceChatConnectionState : uint8 {
    New,
    Connecting,
    Connected,
    Disconnected,
    Failed,
    Closed
};

UENUM(BlueprintType)
enum class EEmbeddedVoiceChatGatheringState : uint8 {
    New,
    InProgress,
    Complete
};

UENUM(BlueprintType)
enum class EEmbeddedVoiceChatSignalingState : uint8 {
    Stable,
    HaveLocalOffer,
    HaveRemoteOffer,
    HaveLocalPranswer,
    HaveRemotePranswer
};

UENUM(BlueprintType)
enum class EEmbeddedVoiceChatDescriptionType : uint8 {
    Unspec,
    Offer,
    Answer,
    Pranswer,
    Rollback
};

class UEmbeddedVoiceChatChannel;

/**
 * the connection handler for a p2p connection
 **/
UCLASS(Blueprintable)
class EMBEDDEDVOICECHAT_API UEmbeddedVoiceChatConnectionHandler : public UObject {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, Category = "Embedded Voice Chat")
    void onStateChange(const EEmbeddedVoiceChatConnectionState &state);

    UFUNCTION(BlueprintNativeEvent, Category = "Embedded Voice Chat")
    void onGatheringStateChange(const EEmbeddedVoiceChatGatheringState &state);

    UFUNCTION(BlueprintNativeEvent, Category = "Embedded Voice Chat")
    void onSignalingStateChange(const EEmbeddedVoiceChatSignalingState &state);

    UFUNCTION(BlueprintNativeEvent, Category = "Embedded Voice Chat")
    void onLocalDescription(const EEmbeddedVoiceChatDescriptionType &descriptionType, const FString &description);

    UFUNCTION(BlueprintNativeEvent, Category = "Embedded Voice Chat")
    void onLocalCandidate(const FString &mid, const FString &candidate);

    UFUNCTION(BlueprintNativeEvent, Category = "Embedded Voice Chat")
    void onDataChannel(const FString &channelId, const UEmbeddedVoiceChatChannel *channel);

#if WITH_EMBEDDEDVOICECHAT
    std::weak_ptr<EmbeddedVoiceChat::ConnectionHandler> toEmbeddedVoiceChat();
    std::shared_ptr<EmbeddedVoiceChat::ConnectionHandler> handler;
#endif
};

/**
 * a p2p connection
**/
UCLASS(BlueprintType)
class EMBEDDEDVOICECHAT_API UEmbeddedVoiceChatConnection : public UObject {
    GENERATED_BODY()

public:
#if WITH_EMBEDDEDVOICECHAT
    std::shared_ptr<EmbeddedVoiceChat::Connection> EmbeddedVoiceChatConnection;
#endif

    /**
     * construct a UEmbeddedVoiceChatConnection
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    static UEmbeddedVoiceChatConnection *createConnection();

    /**
     * connect to a stun server and request Description and Candidate
     * \param stunServer the public domain of a stun server
     * \param stunPort the port of the stun server
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    void connect(const TArray<FString> &iceServers, const int portRangeBegin, const int portRangeEnd);

    /**
     * bind a connection handler
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    void registerConnectionHandler(UEmbeddedVoiceChatConnectionHandler *connectionHandler);

    /**
     * create a channel in the p2p connection
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    UEmbeddedVoiceChatChannel *createChannel(const FEmbeddedVoiceChatChannelId &channelId);

    /**
     * set p2p connection's remote description. set it to the description of the connection you want to connect with.
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    void setRemoteDescription(const EEmbeddedVoiceChatDescriptionType &descriptionType, const FString &description);

    /**
     * set p2p connection's remote candidate. set it to the candidate of the connection you want to connect with.
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    void addRemoteCandidate(const FString &mid, const FString &candidate);

    /**
     * close a peer connection
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    void close();
};

/**
 * the channel handler for a p2p connection channel
 **/
UCLASS(Blueprintable)
class EMBEDDEDVOICECHAT_API UEmbeddedVoiceChatChannelHandler : public UObject {
GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, Category = "Embedded Voice Chat")
    void onOpen();

    UFUNCTION(BlueprintNativeEvent, Category = "Embedded Voice Chat")
    void onClosed();

    UFUNCTION(BlueprintNativeEvent, Category = "Embedded Voice Chat")
    void onError(const FString &error);

    UFUNCTION(BlueprintNativeEvent, Category = "Embedded Voice Chat")
    void onMessage(const FString &message);

#if WITH_EMBEDDEDVOICECHAT
    std::weak_ptr<EmbeddedVoiceChat::ChannelHandler> toEmbeddedVoiceChat();
    std::shared_ptr<EmbeddedVoiceChat::ChannelHandler> handler;
#endif
};

/**
 * a data channel between 2 clients
**/
UCLASS(BlueprintType)
class EMBEDDEDVOICECHAT_API UEmbeddedVoiceChatChannel : public UObject {
    GENERATED_BODY()

public:
#if WITH_EMBEDDEDVOICECHAT
    std::shared_ptr<EmbeddedVoiceChat::Channel> EmbeddedVoiceChatChannel;
#endif

    ~UEmbeddedVoiceChatChannel();

    /**
     * bind a channel handler
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    void registerChannelHandler(UEmbeddedVoiceChatChannelHandler *channelHandler);

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
     * true means success. false means failure
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    bool send(const FString &data);

    /**
     * \return close a channel
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    void close();

    /**
    * set the channel type and 3d properties
    */
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    void setChannelTypeAnd3DProperties(EEmbeddedVoiceChatChannelType type, FEmbeddedVoiceChatChannel3DProperties properties);

    /**
     * \return true if this channel has received voice package in the last isChannelTalkingThreshold milliseconds
    **/
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    bool isTalking();
};
