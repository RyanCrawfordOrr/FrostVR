/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#ifndef EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATDEVICES_H
#define EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATDEVICES_H

#include "miniaudio.h"

#include "EmbeddedVoiceChat_EXPORTS.h"
#include "EmbeddedVoiceChatDevice.h"
#include "EmbeddedVoiceChatCommon.h"

namespace EmbeddedVoiceChat {
    class EMBEDDED_VOICE_CHAT_API Devices {
    public:
        ~Devices();

        std::vector<std::weak_ptr<Device>> getAvailableDevices() const;

        std::weak_ptr<Device> getDefaultDevice() const;

        virtual Result setActiveDevice(std::weak_ptr<Device> device);

        virtual Result setActiveDevice(const Device *device);

        std::weak_ptr<Device> getActiveDevice() const;

        /*
         * refresh the device list. if there is active device, will stop and restart it. if the active device can't be found, will start default device instead.
         * */
        virtual Result refresh() = 0;

        std::unordered_map<unsigned int, std::function<void(void *)>> onRefreshCompleted;
        std::unordered_map<unsigned int, void *> onRefreshCompletedUserData;
    protected:
        std::unordered_map<ma_device_id, std::shared_ptr<Device>> availableDevices;

        std::shared_ptr<Device> defaultDevice;

        std::shared_ptr<Device> activeDevice;
    };
}

extern "C" {
EMBEDDED_VOICE_CHAT_API int EmbeddedVoiceChat_Devices_GetAvailableDeviceCount(EmbeddedVoiceChat::Devices *devices);
EMBEDDED_VOICE_CHAT_API void EmbeddedVoiceChat_Devices_GetAvailableDevices(EmbeddedVoiceChat::Devices *devices, EmbeddedVoiceChat::Device **availableDevices, int *deviceCount);
EMBEDDED_VOICE_CHAT_API EmbeddedVoiceChat::Device *EmbeddedVoiceChat_Devices_GetDefaultDevice(EmbeddedVoiceChat::Devices *devices);
EMBEDDED_VOICE_CHAT_API EmbeddedVoiceChat::Result *EmbeddedVoiceChat_Devices_SetActiveDevice(EmbeddedVoiceChat::Devices *devices, EmbeddedVoiceChat::Device *device);
EMBEDDED_VOICE_CHAT_API EmbeddedVoiceChat::Device *EmbeddedVoiceChat_Devices_GetActiveDevice(EmbeddedVoiceChat::Devices *devices);
EMBEDDED_VOICE_CHAT_API EmbeddedVoiceChat::Result *EmbeddedVoiceChat_Devices_Refresh(EmbeddedVoiceChat::Devices *devices);
EMBEDDED_VOICE_CHAT_API void EmbeddedVoiceChat_Devices_AddOnRefreshCompletedHandler(EmbeddedVoiceChat::Devices *devices, int id, void (*handler)(void *), void* userData = nullptr);
EMBEDDED_VOICE_CHAT_API void EmbeddedVoiceChat_Devices_RemoveOnRefreshCompletedHandler(EmbeddedVoiceChat::Devices *devices, int id);
EMBEDDED_VOICE_CHAT_API void EmbeddedVoiceChat_Devices_ClearOnRefreshCompletedHandler(EmbeddedVoiceChat::Devices *devices);
}

#endif //EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATDEVICES_H
