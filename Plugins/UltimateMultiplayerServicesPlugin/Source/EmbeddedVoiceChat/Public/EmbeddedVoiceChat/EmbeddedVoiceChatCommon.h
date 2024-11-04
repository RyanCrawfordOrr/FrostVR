/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, Feb 2022
 */

#ifndef EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATCOMMON_H
#define EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATCOMMON_H

#include <string>
#include <unordered_map>
#include <memory>

#include "miniaudio.h"
#include "rnnoise.h"

#include "EmbeddedVoiceChat_EXPORTS.h"
#include "EmbeddedVoiceChatChannel3DProperties.h"
#include "EmbeddedVoiceChatChannel.h"

namespace EmbeddedVoiceChat {
    enum class EMBEDDED_VOICE_CHAT_API LogLevel : unsigned char {
        None = 0,
        Fatal = 1,
        Error = 2,
        Warning = 3,
        Info = 4,
        Debug = 5,
        Verbose = 6
    };

    class EMBEDDED_VOICE_CHAT_API LogInterface {
    public:
        /**
         * Does a printf style output to the output stream. Don't use this, it's unsafe. See LogStream
         */
        virtual void Log(LogLevel logLevel, const char *tag, const char *formatStr, ...) = 0;
    };

    class EMBEDDED_VOICE_CHAT_API DefaultLog : public LogInterface {
    private:
        void (*logHandler)(unsigned char level, const char *tag, const char *log);

    public:
        DefaultLog(void (*logHandler)(unsigned char level, const char *tag, const char *log));

        void Log(LogLevel level, const char *tag, const char *formatStr, ...);
    };

    class EMBEDDED_VOICE_CHAT_API Result {
    public:
        Result(const bool &success = true);

        Result(const std::string &text, const bool &success = false);

        const std::string &getText() const;

        bool ok() const;

    private:
        std::string text;
        bool success;
    };

	struct EMBEDDED_VOICE_CHAT_API Listener3DPosition {
		bool bIsSet = false;
		float location[3];
		float direction[3];
		float velocity[3];
	};

#if Allow_Voice_Debug
    EMBEDDED_VOICE_CHAT_API extern ma_encoder_config recordEncoderConfig, noiseSuppressionEncoderConfig, outputEncoderConfig;
    EMBEDDED_VOICE_CHAT_API extern ma_encoder recordEncoder, noiseSuppressionEncoder, outputEncoder;
#endif
    EMBEDDED_VOICE_CHAT_API extern bool bEnableVoiceDebug;

    EMBEDDED_VOICE_CHAT_API extern ma_context context;
    EMBEDDED_VOICE_CHAT_API extern DenoiseState *denoiseState;

	EMBEDDED_VOICE_CHAT_API void enableNoiseSuppression();
	EMBEDDED_VOICE_CHAT_API void disableNoiseSuppression();

    EMBEDDED_VOICE_CHAT_API extern bool muted;
    EMBEDDED_VOICE_CHAT_API extern bool deafened;
    EMBEDDED_VOICE_CHAT_API extern int sampleRate;
    EMBEDDED_VOICE_CHAT_API extern int voiceRatio;

    EMBEDDED_VOICE_CHAT_API extern int isClientTalkingThreshold;
    EMBEDDED_VOICE_CHAT_API extern int isChannelTalkingThreshold;

    // should be set before creating any channel
    EMBEDDED_VOICE_CHAT_API extern int outputChannelCount;

    // global default channel settings. can be set for each channel.
    EMBEDDED_VOICE_CHAT_API extern ChannelType channelType;
    EMBEDDED_VOICE_CHAT_API extern Channel3DProperties channel3DProperties;

	EMBEDDED_VOICE_CHAT_API extern std::mutex channelsMutex;
    EMBEDDED_VOICE_CHAT_API extern std::unordered_map<std::string, std::weak_ptr<Channel>> channels;

    EMBEDDED_VOICE_CHAT_API extern std::weak_ptr<LogInterface> logInterface;

    EMBEDDED_VOICE_CHAT_API extern Listener3DPosition listener3DPosition;

	EMBEDDED_VOICE_CHAT_API void updateListener3DPosition(float location[3], float direction[3], float velocity[3]);
}

extern "C" {
static std::shared_ptr<EmbeddedVoiceChat::DefaultLog> defaultLog;
EMBEDDED_VOICE_CHAT_API void EmbeddedVoiceChat_Common_SetDefaultLog(
        void (*logHandler)(unsigned char level, const char *tag, const char *log));
EMBEDDED_VOICE_CHAT_API void EmbeddedVoiceChat_Common_UnsetDefaultLog();

EMBEDDED_VOICE_CHAT_API bool EmbeddedVoiceChat_Result_Success(EmbeddedVoiceChat::Result *result);
EMBEDDED_VOICE_CHAT_API char *EmbeddedVoiceChat_Result_GetText(EmbeddedVoiceChat::Result *result);

EMBEDDED_VOICE_CHAT_API void EmbeddedVoiceChat_Common_SetEnableNoiseSuppression(bool bEnableNoiseSuppression);
EMBEDDED_VOICE_CHAT_API bool EmbeddedVoiceChat_Common_GetEnableNoiseSuppression();

EMBEDDED_VOICE_CHAT_API void EmbeddedVoiceChat_Common_SetMuted(bool muted);
EMBEDDED_VOICE_CHAT_API bool EmbeddedVoiceChat_Common_GetMuted();
EMBEDDED_VOICE_CHAT_API void EmbeddedVoiceChat_Common_SetDeafened(bool deafened);
EMBEDDED_VOICE_CHAT_API bool EmbeddedVoiceChat_Common_GetDeafened();
EMBEDDED_VOICE_CHAT_API void EmbeddedVoiceChat_Common_SetSampleRate(int sampleRate);
EMBEDDED_VOICE_CHAT_API int EmbeddedVoiceChat_Common_GetSampleRate();
EMBEDDED_VOICE_CHAT_API void EmbeddedVoiceChat_Common_SetVoiceRatio(int voiceRatio);
EMBEDDED_VOICE_CHAT_API int EmbeddedVoiceChat_Common_GetVoiceRatio();

EMBEDDED_VOICE_CHAT_API void EmbeddedVoiceChat_Common_SetIsClientTalkingThreshold(int isClientTalkingThreshold);
EMBEDDED_VOICE_CHAT_API int EmbeddedVoiceChat_Common_GetIsClientTalkingThreshold();
EMBEDDED_VOICE_CHAT_API void EmbeddedVoiceChat_Common_SetIsChannelTalkingThreshold(int isChannelTalkingThreshold);
EMBEDDED_VOICE_CHAT_API int EmbeddedVoiceChat_Common_GetIsChannelTalkingThreshold();

// should be set before creating any channel
EMBEDDED_VOICE_CHAT_API void EmbeddedVoiceChat_Common_SetOutputChannelCount(int outputChannelCount);
EMBEDDED_VOICE_CHAT_API int EmbeddedVoiceChat_Common_GetOutputChannelCount();

EMBEDDED_VOICE_CHAT_API void
EmbeddedVoiceChat_Common_SetChannelTypeAnd3DProperties(unsigned char channelType, int audibleDistance,
                                                       int conversationalDistance,
                                                       float audioFadeIntensityByDistance,
                                                       unsigned char audioFadeModel);
}

#endif //EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATCOMMON_H
