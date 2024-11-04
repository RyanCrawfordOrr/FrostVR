/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#ifndef EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATINPUTDEVICES_H
#define EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATINPUTDEVICES_H

#include "EmbeddedVoiceChat_EXPORTS.h"
#include "EmbeddedVoiceChatDevice.h"
#include "EmbeddedVoiceChatDevices.h"

namespace EmbeddedVoiceChat {
    class EMBEDDED_VOICE_CHAT_API InputDevices : public Devices {
        // @TODO: callback for device hot plug
    public:
        InputDevices();

        Result setActiveDevice(std::weak_ptr<Device>) override;

        Result setActiveDevice(const Device *device) override;

        /*
         * refresh the device list. if there is active device, will stop and restart it. if the active device can't be found, will start default device instead.
         * */
        Result refresh() override;
    private:
    };
}


#endif //EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATINPUTDEVICES_H
