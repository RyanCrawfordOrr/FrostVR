/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, Feb 2022
 */

#ifndef EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATCHANNELID_H
#define EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATCHANNELID_H

#include <string>

#include "EmbeddedVoiceChat_EXPORTS.h"
#include "EmbeddedVoiceChatChannel3DProperties.h"

namespace EmbeddedVoiceChat {

    /*
     * The unique identifier for a channel. Channels are created and destroyed automatically on demand.
     */
    class EMBEDDED_VOICE_CHAT_API ChannelId {
    public:
        /**
         * \brief Constructor
         * \param id The unique channel id you assigned to the channel
         */
        ChannelId(const std::string& id);

        const std::string &getId() const;
    private:
        std::string id;
    };
}


#endif //EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATCHANNELID_H
