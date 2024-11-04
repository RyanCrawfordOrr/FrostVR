/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, Feb 2022
 */

#include "EmbeddedVoiceChatChannel.h"
#include "GenericPlatform/GenericPlatformOutputDevices.h"
#include "Misc/OutputDeviceFile.h"
#include "Engine/Engine.h"

#if WITH_EMBEDDEDVOICECHAT
EEmbeddedVoiceChatConnectionState fromEmbeddedVoiceChat(const EmbeddedVoiceChat::ConnectionState &state) {
    return (EEmbeddedVoiceChatConnectionState)state;
}

EEmbeddedVoiceChatGatheringState fromEmbeddedVoiceChat(const EmbeddedVoiceChat::GatheringState &state) {
    return (EEmbeddedVoiceChatGatheringState)state;
}

EEmbeddedVoiceChatSignalingState fromEmbeddedVoiceChat(const EmbeddedVoiceChat::SignalingState &state) {
    return (EEmbeddedVoiceChatSignalingState)state;
}

EmbeddedVoiceChat::DescriptionType toEmbeddedVoiceChat(const EEmbeddedVoiceChatDescriptionType &type) {
    return (EmbeddedVoiceChat::DescriptionType)type;
}

EEmbeddedVoiceChatDescriptionType fromEmbeddedVoiceChat(const EmbeddedVoiceChat::DescriptionType &type) {
    return (EEmbeddedVoiceChatDescriptionType)type;
}
#endif

void UEmbeddedVoiceChatConnectionHandler::onStateChange_Implementation(const EEmbeddedVoiceChatConnectionState &state) {
}

void UEmbeddedVoiceChatConnectionHandler::onGatheringStateChange_Implementation(const EEmbeddedVoiceChatGatheringState &state) {
}

void UEmbeddedVoiceChatConnectionHandler::onSignalingStateChange_Implementation(const EEmbeddedVoiceChatSignalingState &state) {
}

void UEmbeddedVoiceChatConnectionHandler::onLocalDescription_Implementation(const EEmbeddedVoiceChatDescriptionType &descriptionType, const FString &description) {
}

void UEmbeddedVoiceChatConnectionHandler::onLocalCandidate_Implementation(const FString &mid, const FString &candidate) {
}

void UEmbeddedVoiceChatConnectionHandler::onDataChannel_Implementation(const FString &channelId, const UEmbeddedVoiceChatChannel *channel) {
}

#if WITH_EMBEDDEDVOICECHAT
class UnrealConnectionHandler : public EmbeddedVoiceChat::ConnectionHandler {
public:
    TWeakObjectPtr<UEmbeddedVoiceChatConnectionHandler> handler;

    virtual void onStateChange(const EmbeddedVoiceChat::ConnectionState &state) override {
        if (this->handler.IsValid()) {
            this->handler->onStateChange(fromEmbeddedVoiceChat(state));
        }
    };

    virtual void onGatheringStateChange(const EmbeddedVoiceChat::GatheringState &state) override {
        if (this->handler.IsValid()) {
            this->handler->onGatheringStateChange(fromEmbeddedVoiceChat(state));
        }
    };

    virtual void onSignalingStateChange(const EmbeddedVoiceChat::SignalingState &state) override {
        if (this->handler.IsValid()) {
            this->handler->onSignalingStateChange(fromEmbeddedVoiceChat(state));
        }
    };

    virtual void onLocalDescription(const EmbeddedVoiceChat::DescriptionType &descriptionType, const std::string &description) override {
        if (this->handler.IsValid()) {
            this->handler->onLocalDescription(fromEmbeddedVoiceChat(descriptionType), UTF8_TO_TCHAR(description.c_str()));
        }
    };

    virtual void onLocalCandidate(const std::string &mid, const std::string &candidate) override {
        if (this->handler.IsValid()) {
            this->handler->onLocalCandidate(UTF8_TO_TCHAR(mid.c_str()), UTF8_TO_TCHAR(candidate.c_str()));
        }
    };

    virtual void onDataChannel(std::shared_ptr<EmbeddedVoiceChat::Channel> channel) override {
        if (this->handler.IsValid()) {
            UEmbeddedVoiceChatChannel *EmbeddedVoiceChatChannel = NewObject<UEmbeddedVoiceChatChannel>();
            EmbeddedVoiceChatChannel->EmbeddedVoiceChatChannel = channel;
            this->handler->onDataChannel(UTF8_TO_TCHAR(channel->getChannelId().getId().c_str()), EmbeddedVoiceChatChannel);
        }
    };
};

std::weak_ptr<EmbeddedVoiceChat::ConnectionHandler> UEmbeddedVoiceChatConnectionHandler::toEmbeddedVoiceChat() {
    std::shared_ptr<UnrealConnectionHandler> connectionHandler = std::make_shared<UnrealConnectionHandler>();
    connectionHandler->handler = this;
    this->handler = connectionHandler;
    return this->handler;
}
#endif

UEmbeddedVoiceChatConnection *UEmbeddedVoiceChatConnection::createConnection() {
#if WITH_EMBEDDEDVOICECHAT
    UEmbeddedVoiceChatConnection *connection = NewObject<UEmbeddedVoiceChatConnection>();
    connection->EmbeddedVoiceChatConnection = EmbeddedVoiceChat::Connection::create();
    return connection;
#endif
    return nullptr;
}

void UEmbeddedVoiceChatConnection::connect(const TArray<FString> &iceServers, const int portRangeBegin, const int portRangeEnd) {
#if WITH_EMBEDDEDVOICECHAT
    if (this->EmbeddedVoiceChatConnection) {
        std::vector<std::string> servers;
        for (const auto& elem : iceServers) {
            servers.emplace_back(TCHAR_TO_UTF8(*elem));
        }
        this->EmbeddedVoiceChatConnection->connect(servers, portRangeBegin, portRangeEnd);
    }
#endif
}

void UEmbeddedVoiceChatConnection::registerConnectionHandler(UEmbeddedVoiceChatConnectionHandler *connectionHandler) {
#if WITH_EMBEDDEDVOICECHAT
    if (this->EmbeddedVoiceChatConnection) {
        this->EmbeddedVoiceChatConnection->registerConnectionHandler(connectionHandler->toEmbeddedVoiceChat());
    }
#endif
}

UEmbeddedVoiceChatChannel *UEmbeddedVoiceChatConnection::createChannel(const FEmbeddedVoiceChatChannelId &channelId) {
#if WITH_EMBEDDEDVOICECHAT
    if (this->EmbeddedVoiceChatConnection) {
        UEmbeddedVoiceChatChannel *channel = NewObject<UEmbeddedVoiceChatChannel>();
        channel->EmbeddedVoiceChatChannel = this->EmbeddedVoiceChatConnection->createChannel(channelId.toEmbeddedVoiceChat());
        return channel;
    }
#endif
    return nullptr;
}

void UEmbeddedVoiceChatConnection::setRemoteDescription(const EEmbeddedVoiceChatDescriptionType &descriptionType, const FString &description) {
#if WITH_EMBEDDEDVOICECHAT
    if (this->EmbeddedVoiceChatConnection) {
        this->EmbeddedVoiceChatConnection->setRemoteDescription(toEmbeddedVoiceChat(descriptionType), TCHAR_TO_UTF8(*description));
    }
#endif
}

void UEmbeddedVoiceChatConnection::addRemoteCandidate(const FString &mid, const FString &candidate) {
#if WITH_EMBEDDEDVOICECHAT
    if (this->EmbeddedVoiceChatConnection) {
        this->EmbeddedVoiceChatConnection->addRemoteCandidate(TCHAR_TO_UTF8(*mid), TCHAR_TO_UTF8(*candidate));
    }
#endif
}

void UEmbeddedVoiceChatConnection::close() {
#if WITH_EMBEDDEDVOICECHAT
    if (this->EmbeddedVoiceChatConnection) {
        this->EmbeddedVoiceChatConnection->close();
    }
#endif
}

void UEmbeddedVoiceChatChannelHandler::onOpen_Implementation() {
}

void UEmbeddedVoiceChatChannelHandler::onClosed_Implementation() {
}

void UEmbeddedVoiceChatChannelHandler::onError_Implementation(const FString &error) {
}

void UEmbeddedVoiceChatChannelHandler::onMessage_Implementation(const FString &message) {
}

#if WITH_EMBEDDEDVOICECHAT
class UnrealChannelHandler : public EmbeddedVoiceChat::ChannelHandler {
public:
    TWeakObjectPtr<UEmbeddedVoiceChatChannelHandler> handler;

    virtual void onOpen() override {
        if (this->handler.IsValid()) {
            this->handler->onOpen();
        }
    };

    virtual void onClosed() override {
        if (this->handler.IsValid()) {
            this->handler->onClosed();
        }
    };

    virtual void onError(const std::string &error) override {
        if (this->handler.IsValid()) {
            this->handler->onError(UTF8_TO_TCHAR(error.c_str()));
        }
    };

    virtual void onMessage(const std::string &message) override {
        if (this->handler.IsValid()) {
            this->handler->onMessage(UTF8_TO_TCHAR(message.c_str()));
        }
    };
};

std::weak_ptr<EmbeddedVoiceChat::ChannelHandler> UEmbeddedVoiceChatChannelHandler::toEmbeddedVoiceChat() {
    std::shared_ptr<UnrealChannelHandler> channelHandler = std::make_shared<UnrealChannelHandler>();
    channelHandler->handler = this;
    this->handler = channelHandler;
    return this->handler;
}
#endif

void UEmbeddedVoiceChatChannel::registerChannelHandler(UEmbeddedVoiceChatChannelHandler *channelHandler) {
#if WITH_EMBEDDEDVOICECHAT
    if (this->EmbeddedVoiceChatChannel) {
        this->EmbeddedVoiceChatChannel->registerChannelHandler(channelHandler->toEmbeddedVoiceChat());
    }
#endif
}

UEmbeddedVoiceChatChannel::~UEmbeddedVoiceChatChannel() {
    LOG_EMBEDDEDVOICECHAT_NORMAL("UEmbeddedVoiceChatChannel destroyed. ");
}

void UEmbeddedVoiceChatChannel::setVolume(float volume) {
#if WITH_EMBEDDEDVOICECHAT
    if (this->EmbeddedVoiceChatChannel) {
        this->EmbeddedVoiceChatChannel->setVolume(volume);
    }
#endif
}

float UEmbeddedVoiceChatChannel::getVolume() {
#if WITH_EMBEDDEDVOICECHAT
    if (this->EmbeddedVoiceChatChannel) {
        return this->EmbeddedVoiceChatChannel->getVolume();
    }
#endif
    return -1.0f;
}

void UEmbeddedVoiceChatChannel::update3DPosition(const FVector &location, const FVector &direction, const FVector &velocity) {
#if WITH_EMBEDDEDVOICECHAT
    if (this->EmbeddedVoiceChatChannel) {
        float l[3] = {static_cast<float>(location.X), static_cast<float>(location.Y), static_cast<float>(location.Z)};
        float d[3] = {static_cast<float>(direction.X), static_cast<float>(direction.Y), static_cast<float>(direction.Z)};
        float v[3] = {static_cast<float>(velocity.X), static_cast<float>(velocity.Y), static_cast<float>(velocity.Z)};
        this->EmbeddedVoiceChatChannel->update3DPosition(l, d, v);
    }
#endif
}

void UEmbeddedVoiceChatChannel::updateListener3DPosition(const FVector &location, const FVector &direction, const FVector &velocity) {
#if WITH_EMBEDDEDVOICECHAT
    if (this->EmbeddedVoiceChatChannel) {
        float l[3] = {static_cast<float>(location.X), static_cast<float>(location.Y), static_cast<float>(location.Z)};
        float d[3] = {static_cast<float>(direction.X), static_cast<float>(direction.Y), static_cast<float>(direction.Z)};
        float v[3] = {static_cast<float>(velocity.X), static_cast<float>(velocity.Y), static_cast<float>(velocity.Z)};
        this->EmbeddedVoiceChatChannel->updateListener3DPosition(l, d, v);
    }
#endif
}

bool UEmbeddedVoiceChatChannel::send(const FString &data) {
#if WITH_EMBEDDEDVOICECHAT
    if (this->EmbeddedVoiceChatChannel) {
        return this->EmbeddedVoiceChatChannel->send(TCHAR_TO_UTF8(*data));
    }
#endif
    return false;
}

void UEmbeddedVoiceChatChannel::close() {
#if WITH_EMBEDDEDVOICECHAT
    if (this->EmbeddedVoiceChatChannel) {
        this->EmbeddedVoiceChatChannel->close();
    }
#endif
}

void UEmbeddedVoiceChatChannel::setChannelTypeAnd3DProperties(EEmbeddedVoiceChatChannelType type, FEmbeddedVoiceChatChannel3DProperties properties) {
#if WITH_EMBEDDEDVOICECHAT
    if (this->EmbeddedVoiceChatChannel) {
        this->EmbeddedVoiceChatChannel->setChannelTypeAnd3DProperties((EmbeddedVoiceChat::ChannelType)type, properties.toEmbeddedVoiceChat());
    }
#endif
}

bool UEmbeddedVoiceChatChannel::isTalking() {
#if WITH_EMBEDDEDVOICECHAT
    if (this->EmbeddedVoiceChatChannel) {
        return this->EmbeddedVoiceChatChannel->isTalking();
    }
#endif
    return false;
}