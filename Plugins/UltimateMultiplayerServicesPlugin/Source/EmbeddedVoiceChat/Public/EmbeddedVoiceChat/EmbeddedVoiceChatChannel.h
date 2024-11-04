/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, Feb 2022
 */

#ifndef EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATCHANNEL_H
#define EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATCHANNEL_H

#include <queue>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <thread>
#include <unordered_map>

#include "rtc/rtc.hpp"
#include "opus.h"
#include "miniaudio.h"

#include "EmbeddedVoiceChat_EXPORTS.h"
#include "EmbeddedVoiceChatChannelId.h"
#include "EmbeddedVoiceChatChannel3DProperties.h"

namespace EmbeddedVoiceChat {
    enum class EMBEDDED_VOICE_CHAT_API ConnectionState : unsigned char {
        New,
        Connecting,
        Connected,
        Disconnected,
        Failed,
        Closed
    };

    enum class EMBEDDED_VOICE_CHAT_API GatheringState : unsigned char {
        New,
        InProgress,
        Complete
    };

    enum class EMBEDDED_VOICE_CHAT_API SignalingState : unsigned char {
        Stable,
        HaveLocalOffer,
        HaveRemoteOffer,
        HaveLocalPranswer,
        HaveRemotePranswer,
    };

    enum class EMBEDDED_VOICE_CHAT_API DescriptionType : unsigned char {
        Unspec,
        Offer,
        Answer,
        Pranswer,
        Rollback
    };

    class Channel;

    class EMBEDDED_VOICE_CHAT_API ConnectionHandler {
    public:
        virtual ~ConnectionHandler() {};

        virtual void onStateChange(const ConnectionState &state) = 0;

        virtual void onGatheringStateChange(const GatheringState &state) = 0;

        virtual void onSignalingStateChange(const SignalingState &state) = 0;

        virtual void onLocalDescription(const DescriptionType &descriptionType, const std::string &description) = 0;

        virtual void onLocalCandidate(const std::string &mid, const std::string &candidate) = 0;

        virtual void onDataChannel(std::shared_ptr<Channel> channel) = 0;
    };

    /*
     *
     */
    class EMBEDDED_VOICE_CHAT_API Connection : public std::enable_shared_from_this<Connection> {
    public:
        static std::shared_ptr<Connection> create();

        Connection() = default;

        ~Connection();

        void connect(const std::vector<std::string> &iceServers, int portRangeBegin, int portRangeEnd);

        void registerConnectionHandler(std::weak_ptr<ConnectionHandler> connectionHandler);

        std::shared_ptr<Channel> createChannel(const ChannelId &channelId);

        void setRemoteDescription(const DescriptionType &descriptionType, const std::string &description);

        void addRemoteCandidate(const std::string &mid, const std::string &candidate);

        void close();

        std::shared_ptr<ConnectionHandler> connectionHandlerSpt;
    private:

        std::shared_ptr<rtc::PeerConnection> peerConnection;
        std::weak_ptr<ConnectionHandler> connectionHandler;
    };

    class EMBEDDED_VOICE_CHAT_API ConnectionHolder {
    public:
        std::shared_ptr<EmbeddedVoiceChat::Connection> connection;
    };

    class EMBEDDED_VOICE_CHAT_API ChannelHandler {
    public:
        virtual ~ChannelHandler() {};

        virtual void onOpen() = 0;

        virtual void onClosed() = 0;

        virtual void onError(const std::string &error) = 0;

        virtual void onMessage(const std::string &message) = 0;
    };

    class EMBEDDED_VOICE_CHAT_API ChannelAudioHandler {
    public:
        virtual void onAudioData(std::queue<float> cache, const unsigned int frameCount) = 0;
    };

    /*
     * A connection to a channel
     */
    class EMBEDDED_VOICE_CHAT_API Channel : public std::enable_shared_from_this<Channel> {
    public:
        static std::shared_ptr<Channel>
        create(const ChannelId &channelId, std::shared_ptr<rtc::DataChannel> dataChannel);

        ~Channel();

        ChannelId getChannelId() const;

        void registerChannelHandler(std::weak_ptr<ChannelHandler> channelHandler);

        void registerChannelAudioHandler(std::weak_ptr<ChannelAudioHandler> channelAudioHandler);

        /*
         * \param volume 0.0 means muted, 1.0 means normal
         * */
        void setVolume(float volume);

        float getVolume();

        /*
         * deprecated. For internal use only
         * \param direction for doppler effect
         * \param velocity for doppler effect
         * */
        void update3DPosition(float location[3], float direction[3], float velocity[3]);

		/*
		 * deprecated. Use EmbeddedVoiceChat::updateListener3DPosition instead.
		 * */
        void updateListener3DPosition(float location[3], float direction[3], float velocity[3]);

        bool send(const std::string &data);

        /*
         * \brief internal use only
         * */
        bool send(const rtc::binary &data);

        void getCacheOnly(std::vector<float> &cache, const unsigned int &frameCount);

        void getCache(std::vector<float> &cache, const unsigned int &frameCount);

        int getCacheSize() const;

        void clearCache();

        bool isOpen() const;

        void close();

        bool processAudio(void *buffer, unsigned int size);

        void setChannelTypeAnd3DProperties(const ChannelType &type, const Channel3DProperties &properties);

        bool isTalking() const;

        std::shared_ptr<ChannelHandler> channelHandlerSpt;
        std::shared_ptr<ChannelAudioHandler> channelAudioHandlerSpt;
    private:
        /**
         * \brief Constructor
         * \param channelId The unique channel id you assigned to the channel
         */
        Channel(const ChannelId &channelId, std::shared_ptr<rtc::DataChannel> dataChannel);

        void initialize();

        void processing();

#if Allow_Voice_Debug
        ma_encoder_config humanVoiceEncoderConfig;
        ma_encoder humanVoiceEncoder;
#endif

        ma_spatializer_listener_config spatializerListenerConfig;
        ma_spatializer_listener spatializerListener;

        ma_spatializer_config spatializerConfig;
        ma_spatializer spatializer;

        ChannelId channelId;

        std::shared_ptr<rtc::DataChannel> dataChannel;

        std::weak_ptr<ChannelHandler> channelHandler;
        std::weak_ptr<ChannelAudioHandler> channelAudioHandler;

        float volume = 1.0f;

        // float as a chain for dynamic output period
        std::mutex cacheMutex;
        std::queue<float> cacheBuffer;

        std::queue<std::vector<std::byte>> audioProcessBuffer;

        bool buffered = false;

        OpusDecoder *decoder;

        std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> lastPackageReceivedTime;
    };

    class EMBEDDED_VOICE_CHAT_API ChannelHolder {
    public:
        std::shared_ptr<EmbeddedVoiceChat::Channel> channel;
    };
}

extern "C" {
EMBEDDED_VOICE_CHAT_API EmbeddedVoiceChat::ConnectionHolder *EmbeddedVoiceChat_Connection_CreateConnection();
EMBEDDED_VOICE_CHAT_API void
EmbeddedVoiceChat_Connection_DestroyConnection(EmbeddedVoiceChat::ConnectionHolder *connection);
EMBEDDED_VOICE_CHAT_API void
EmbeddedVoiceChat_Connection_Connect(EmbeddedVoiceChat::ConnectionHolder *connection, const char **iceServers,
                                     int iceServerCount, int portRangeBegin, int portRangeEnd);
EMBEDDED_VOICE_CHAT_API void EmbeddedVoiceChat_Connection_Close(EmbeddedVoiceChat::ConnectionHolder *connection);
EMBEDDED_VOICE_CHAT_API void
EmbeddedVoiceChat_Connection_SetRemoteDescription(EmbeddedVoiceChat::ConnectionHolder *connection,
                                                  unsigned char descriptionType,
                                                  const char *description);
EMBEDDED_VOICE_CHAT_API void
EmbeddedVoiceChat_Connection_AddRemoteCandidate(EmbeddedVoiceChat::ConnectionHolder *connection, const char *mid,
                                                const char *candidate);
EMBEDDED_VOICE_CHAT_API EmbeddedVoiceChat::ChannelHolder *
EmbeddedVoiceChat_Connection_CreateChannel(EmbeddedVoiceChat::ConnectionHolder *connection, const char *channelId);
EMBEDDED_VOICE_CHAT_API void
EmbeddedVoiceChat_Connection_RegisterConnectionHandler(EmbeddedVoiceChat::ConnectionHolder *connection,
                                                       void (*onStateChange)(unsigned char state, void *),
                                                       void (*onGatheringStateChange)(unsigned char gatheringState,
                                                                                      void *),
                                                       void (*onSignalingStateChange)(unsigned char signingState,
                                                                                      void *),
                                                       void (*onLocalDescription)(unsigned char descriptionType,
                                                                                  const char *description, void *),
                                                       void (*onLocalCandidate)(const char *mid, const char *candidate,
                                                                                void *),
                                                       void (*onDataChannel)(EmbeddedVoiceChat::ChannelHolder *channel,
                                                                             void *), void *userData = nullptr);
EMBEDDED_VOICE_CHAT_API void
EmbeddedVoiceChat_Connection_UnregisterConnectionHandler(EmbeddedVoiceChat::ConnectionHolder *connection);

EMBEDDED_VOICE_CHAT_API void EmbeddedVoiceChat_Connection_DestroyChannel(EmbeddedVoiceChat::ChannelHolder *channel);
EMBEDDED_VOICE_CHAT_API void
EmbeddedVoiceChat_Channel_SetVolume(EmbeddedVoiceChat::ChannelHolder *channel, float volume);
EMBEDDED_VOICE_CHAT_API float EmbeddedVoiceChat_Channel_GetVolume(EmbeddedVoiceChat::ChannelHolder *channel);
EMBEDDED_VOICE_CHAT_API void
EmbeddedVoiceChat_Channel_Update3DPosition(EmbeddedVoiceChat::ChannelHolder *channel, float *location, float *direction,
                                           float *velocity);
EMBEDDED_VOICE_CHAT_API void
EmbeddedVoiceChat_Channel_UpdateListener3DPosition(EmbeddedVoiceChat::ChannelHolder *channel, float *location,
                                                   float *direction, float *velocity);
EMBEDDED_VOICE_CHAT_API bool
EmbeddedVoiceChat_Channel_Send(EmbeddedVoiceChat::ChannelHolder *channel, const char *data);
EMBEDDED_VOICE_CHAT_API void
EmbeddedVoiceChat_Channel_GetCacheOnly(EmbeddedVoiceChat::ChannelHolder *channel, float *cache, int frameCount, int *gotFrameCount);
EMBEDDED_VOICE_CHAT_API void EmbeddedVoiceChat_Channel_Close(EmbeddedVoiceChat::ChannelHolder *channel);
EMBEDDED_VOICE_CHAT_API void
EmbeddedVoiceChat_Channel_SetChannelTypeAnd3DProperties(EmbeddedVoiceChat::ChannelHolder *channel,
                                                        unsigned char channelType,
                                                        int audibleDistance,
                                                        int conversationalDistance, float audioFadeIntensityByDistance,
                                                        unsigned char audioFadeModel);
EMBEDDED_VOICE_CHAT_API bool EmbeddedVoiceChat_Channel_IsTalking(EmbeddedVoiceChat::ChannelHolder *channel);
EMBEDDED_VOICE_CHAT_API void
EmbeddedVoiceChat_Channel_RegisterChannelHandler(EmbeddedVoiceChat::ChannelHolder *channel, void (*onOpen)(void *),
                                                 void (*onClose)(void *), void (*onError)(const char *error, void *),
                                                 void (*onMessage)(const char *message, void *),
                                                 void *userData = nullptr);
EMBEDDED_VOICE_CHAT_API void
EmbeddedVoiceChat_Channel_RegisterChannelAudioHandler(EmbeddedVoiceChat::ChannelHolder *channel,
                                                      void (*onAudioData)(float *, unsigned int, void *),
                                                      void *userData);
EMBEDDED_VOICE_CHAT_API void
EmbeddedVoiceChat_Channel_UnregisterChannelHandler(EmbeddedVoiceChat::ChannelHolder *channel);
EMBEDDED_VOICE_CHAT_API void
EmbeddedVoiceChat_Channel_UnregisterChannelAudioHandler(EmbeddedVoiceChat::ChannelHolder *channel);
}

#endif //EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATCHANNEL_H
