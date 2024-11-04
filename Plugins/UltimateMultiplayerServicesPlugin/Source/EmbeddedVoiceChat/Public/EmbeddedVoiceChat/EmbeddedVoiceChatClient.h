/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, Feb 2022
 */

#ifndef EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATCLIENT_H
#define EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATCLIENT_H

#include <memory>

#include "miniaudio.h"

#include "EmbeddedVoiceChat_EXPORTS.h"
#include "EmbeddedVoiceChatCommon.h"
#include "EmbeddedVoiceChatInputDevices.h"
#include "EmbeddedVoiceChatOutputDevices.h"

namespace EmbeddedVoiceChat {
    class EMBEDDED_VOICE_CHAT_API Client {
    public:
        /*
         * */
        Result initialize(bool enableNoiseSuppression = true);

        Result terminate();

        std::shared_ptr<InputDevices> getInputDevices();

        std::shared_ptr<OutputDevices> getOutputDevices();

        bool isTalking() const;

    private:
        std::shared_ptr<InputDevices> inputDevices;
        std::shared_ptr<OutputDevices> outputDevices;

        ma_context_config config;
        ma_log log;
    };
}

extern "C" {
EMBEDDED_VOICE_CHAT_API EmbeddedVoiceChat::Client *EmbeddedVoiceChat_Client_CreateClient();
EMBEDDED_VOICE_CHAT_API void EmbeddedVoiceChat_Client_DestroyClient(EmbeddedVoiceChat::Client *);
EMBEDDED_VOICE_CHAT_API EmbeddedVoiceChat::Result *
EmbeddedVoiceChat_Client_Initialize(EmbeddedVoiceChat::Client *client, bool enableNoiseSuppression = true);
EMBEDDED_VOICE_CHAT_API EmbeddedVoiceChat::Result *
EmbeddedVoiceChat_Client_Terminate(EmbeddedVoiceChat::Client *client);
EMBEDDED_VOICE_CHAT_API EmbeddedVoiceChat::InputDevices *EmbeddedVoiceChat_Client_GetInputDevices(EmbeddedVoiceChat::Client *client);
EMBEDDED_VOICE_CHAT_API EmbeddedVoiceChat::OutputDevices *EmbeddedVoiceChat_Client_GetOutputDevices(EmbeddedVoiceChat::Client *client);
EMBEDDED_VOICE_CHAT_API bool EmbeddedVoiceChat_Client_IsTalking(EmbeddedVoiceChat::Client *client);
}


#endif //EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATCLIENT_H
