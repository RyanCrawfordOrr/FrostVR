/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#ifndef EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATDEVICE_H
#define EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATDEVICE_H

#include <queue>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <thread>
#include <string>

#include "miniaudio.h"
#include "opus.h"

#include "EmbeddedVoiceChatCommon.h"
#include "EmbeddedVoiceChat_EXPORTS.h"

namespace std {
    template <>
    struct EMBEDDED_VOICE_CHAT_API hash<ma_device_id> {
        std::size_t operator()(const ma_device_id &s) const noexcept;
    };

    template <>
    struct EMBEDDED_VOICE_CHAT_API equal_to<ma_device_id> {
        bool operator()(const ma_device_id &lhs, const ma_device_id &rhs) const;
    };
}

namespace EmbeddedVoiceChat {
    class EMBEDDED_VOICE_CHAT_API DeviceHandler {
    public:
        virtual ~DeviceHandler() {};

        virtual void onStarted() = 0;

        virtual void onStopped() = 0;

        virtual void onInterruptionBegan() = 0;

        virtual void onInterruptionEnded() = 0;
    };

    class EMBEDDED_VOICE_CHAT_API BaseDevice {
    public:
        BaseDevice();

        virtual ~BaseDevice();

        virtual Result start();

        virtual Result stop();

        virtual bool isInputDevice() const = 0;

        virtual bool isOutputDevice() const = 0;

        void processAudio(float *pcm, unsigned int frameCount);

        bool isTalking() const;

	    void getRenderedAudio(std::vector<float> &cache, const unsigned int &frameCount);

        std::shared_ptr<DeviceHandler> deviceHandlerSpt;
    protected:
        virtual void processing();

        std::thread audioProcessThread;
        std::condition_variable audioProcessConditionVariable;
        std::mutex audioProcessMutex;
        std::mutex audioProcessBufferMutex;
        std::queue<float> audioProcessBuffer;
        bool stopAudioProcessing = false;
        bool audioProcessWaiting = false;
        bool processAudioInPlace = false;

        OpusEncoder *encoder = nullptr;

        opus_int32 complexity = 9;
        opus_int32 bitRate = 72000;

        std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> lastVoiceActiveTime;
    };

    class EMBEDDED_VOICE_CHAT_API Device : public BaseDevice {
    public:
        Device(const ma_device_info &deviceInfo, ma_device_type deviceType, std::function<void()> rerouteHandler);

        virtual ~Device();

        const std::string &getName() const;

        const ma_device_id &getId() const;

        virtual Result start() override;

        virtual Result stop() override;

        bool isInputDevice() const override;

        bool isOutputDevice() const override;

        void registerDeviceHandler(std::weak_ptr<DeviceHandler> deviceHandler);

        /**
         * internal use only
         * */
        void onStarted();

        void onStopped();

        void onRerouted();

        void onInterruptionBegan();

        void onInterruptionEnded();

        std::shared_ptr<DeviceHandler> deviceHandlerSpt;
    private:
        std::string deviceName;
        ma_device_id id;

        ma_device_type deviceType;

        ma_device_config config;
        ma_device device;

        std::weak_ptr<DeviceHandler> deviceHandler;
        std::function<void()> rerouteHandler;
    };

    class EMBEDDED_VOICE_CHAT_API AbstractCaptureDevice : public BaseDevice {
    public:
        bool isInputDevice() const override;

        bool isOutputDevice() const override;
    };

    class EMBEDDED_VOICE_CHAT_API AbstractPlaybackDevice : public BaseDevice {
    public:
        bool isInputDevice() const override;

        bool isOutputDevice() const override;
    };
}

extern "C" {
EMBEDDED_VOICE_CHAT_API char *EmbeddedVoiceChat_Device_GetName(EmbeddedVoiceChat::Device *device);
EMBEDDED_VOICE_CHAT_API void
EmbeddedVoiceChat_Device_RegisterDeviceHandler(EmbeddedVoiceChat::Device *device, void (*onStarted)(void *),
                                               void (*onStopped)(void *), void (*onInterruptionBegan)(void *),
                                               void (*onInterruptionEnded)(void *), void *userData = nullptr);
EMBEDDED_VOICE_CHAT_API void
EmbeddedVoiceChat_Device_UnregisterDeviceHandler(EmbeddedVoiceChat::Device *device);

EMBEDDED_VOICE_CHAT_API EmbeddedVoiceChat::AbstractCaptureDevice *EmbeddedVoiceChat_AbstractCaptureDevice_CreateAbstractCaptureDevice();
EMBEDDED_VOICE_CHAT_API void EmbeddedVoiceChat_AbstractCaptureDevice_DestroyAbstractCaptureDevice(EmbeddedVoiceChat::AbstractCaptureDevice *);
EMBEDDED_VOICE_CHAT_API void EmbeddedVoiceChat_AbstractCaptureDevice_ProcessAudio(EmbeddedVoiceChat::AbstractCaptureDevice *, float *, unsigned int);
}

#endif //EMBEDDEDVOICECHAT_EMBEDDEDVOICECHATDEVICE_H
