/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, Feb 2022
 */

#ifndef EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATCHANNEL3DPROPERTIES_H
#define EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATCHANNEL3DPROPERTIES_H

#include "EmbeddedVoiceChat_EXPORTS.h"

namespace EmbeddedVoiceChat {
    /**
     * \brief The type of channel
     */
    enum EMBEDDED_VOICE_CHAT_API ChannelType {
        /**
         * \brief A typical conferencing channel
         */
        NonPositional,
        /**
         * \brief A conferencing channel where users' voices are rendered with distance.
         */
        Proximity,
        /**
         * \brief A conferencing channel where users' voices are rendered with 3D positional effects.
         */
        Positional
    };

    /**
      * \brief The distance model for a Positional channel, which determines the algorithm to use when computing attenuation
      */
    enum EMBEDDED_VOICE_CHAT_API AudioFadeModel : unsigned char {
        /**
         * \brief conversationalDistance / (conversationalDistance + audioFadeIntensityByDistance * (clamp(distance, conversationalDistance, audibleDistance) - conversationalDistance))
         */
        InverseByDistance,
        /**
         * \brief 1 - audioFadeIntensityByDistance * (clamp(distance, conversationalDistance, audibleDistance) - conversationalDistance) / (audibleDistance - conversationalDistance)
         */
        LinearByDistance,
        /**
         * \brief powd(clamp(distance, conversationalDistance, audibleDistance) / conversationalDistance, -audioFadeIntensityByDistance);
         */
        ExponentialByDistance
    };

    /**
      * \brief Properties to control the 3D effects applied to audio in Positional Channels
      */
    class EMBEDDED_VOICE_CHAT_API Channel3DProperties {
    public:
        Channel3DProperties() = default;

        /**
         * \brief Constructor
         * \param audibleDistance The maximum distance from the listener that a speaker can be heard. Must be > 0.
         * \param conversationalDistance The distance from the listener within which a speaker’s voice is heard at its original volume. Must be >= 0 and <= audibleDistance.
         * \param audioFadeIntensityByDistance How strong the effect of the audio fade is as the speaker moves away from the listener. Must be >= 0.
         * \param audioFadeModel The model used to determine how loud a voice is at different distances.
         */
        Channel3DProperties(const int &audibleDistance, const int &conversationalDistance,
                            const float &audioFadeIntensityByDistance, const AudioFadeModel &audioFadeModel);

        int getAudibleDistance() const;
        int getConversationalDistance() const;
        float getAudioFadeIntensityByDistance() const;
        AudioFadeModel getAudioFadeModel() const;
    private:
        int audibleDistance = 5000;
        int conversationalDistance = 1000;
        float audioFadeIntensityByDistance = 1.0f;
        AudioFadeModel audioFadeModel = AudioFadeModel::LinearByDistance;
    };
}


#endif //EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATCHANNEL3DPROPERTIES_H
