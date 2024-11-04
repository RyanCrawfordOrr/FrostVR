/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, Jan 2023
 */

#include "EmbeddedVoiceChatAudioCapture.h"
#include "EmbeddedVoiceChatGlobals.h"

#include "Math/UnrealMathUtility.h"

#if WITH_EMBEDDEDVOICECHAT

#include "EmbeddedVoiceChat/EmbeddedVoiceChatCommon.h"

#endif

UEmbeddedVoiceChatAudioCapture::UEmbeddedVoiceChatAudioCapture() {
#if WITH_EMBEDDEDVOICECHAT
    this->EmbeddedVoiceChatDevice = std::make_shared<EmbeddedVoiceChat::AbstractCaptureDevice>();
#endif
}

UEmbeddedVoiceChatAudioCapture::~UEmbeddedVoiceChatAudioCapture() {
}

int32 UEmbeddedVoiceChatAudioCapture::GetCaptureDevicesAvailable(TArray<FEmbeddedVoiceChatAudioCaptureDeviceInfo>& OutDevices) {
    TArray<Audio::FCaptureDeviceInfo> Devices;
    int32 num = AudioCapture.GetCaptureDevicesAvailable(Devices);
    for (const auto &device : Devices) {
        FEmbeddedVoiceChatAudioCaptureDeviceInfo OutDevice;
        OutDevice.DeviceName = FName(*device.DeviceName);
        OutDevice.NumInputChannels = device.InputChannels;
        OutDevice.SampleRate = device.PreferredSampleRate;
        OutDevice.DeviceId = device.DeviceId;
        OutDevice.bSupportsHardwareAEC = device.bSupportsHardwareAEC;

        OutDevices.Add(OutDevice);
    }
    return num;
}

bool UEmbeddedVoiceChatAudioCapture::GetCaptureDeviceInfo(FEmbeddedVoiceChatAudioCaptureDeviceInfo& OutInfo, int32 DeviceIndex) {
    Audio::FCaptureDeviceInfo Info;
    if (AudioCapture.GetCaptureDeviceInfo(Info, DeviceIndex)) {
        OutInfo.DeviceName = FName(*Info.DeviceName);
        OutInfo.NumInputChannels = Info.InputChannels;
        OutInfo.SampleRate = Info.PreferredSampleRate;
        OutInfo.DeviceId = Info.DeviceId;
        OutInfo.bSupportsHardwareAEC = Info.bSupportsHardwareAEC;
        return true;
    }
    return false;
}

bool UEmbeddedVoiceChatAudioCapture::OpenCaptureStream(int32 DeviceIndex, int32 NumFramesDesired) {
    if (!AudioCapture.IsStreamOpen()) {
        Audio::FOnAudioCaptureFunction OnCapture = [this, NumFramesDesired](const void* AudioData, int32 NumFrames, int32 InNumChannels, int32 InSampleRate, double StreamTime, bool bOverFlow) {
            LOG_EMBEDDEDVOICECHAT_VERYVERBOSE(FString::Printf(TEXT("captured %d frames in %d sample rate"), NumFrames, InSampleRate));
#if WITH_EMBEDDEDVOICECHAT
            if (this->EmbeddedVoiceChatDevice) {
                float *firstChannelAudioData = (float *)malloc(NumFrames * sizeof(float));
                for (int i = 0; i < NumFrames; i++) {
                    firstChannelAudioData[i] = ((const float*)AudioData)[i * InNumChannels];
                }

                int frameCount = NumFrames;

                if (InSampleRate != 0 && InSampleRate != EmbeddedVoiceChat::sampleRate) {
                    LOG_EMBEDDEDVOICECHAT_VERYVERBOSE(FString::Printf(TEXT("resample sample rate for captured %d frames"), frameCount));

                    int32 MaxOutputFrames = frameCount * EmbeddedVoiceChat::sampleRate / AudioCapture.GetSampleRate() + 16;
                    float *resampled = (float *)malloc(MaxOutputFrames * sizeof(float));
                    int32 NumResampledFrames = frameCount;

                    Resampler.ProcessAudio(firstChannelAudioData, frameCount, false, resampled, MaxOutputFrames, NumResampledFrames);

                    this->EmbeddedVoiceChatDevice->processAudio(resampled, NumResampledFrames);

                    free(resampled);
                } else {
                    LOG_EMBEDDEDVOICECHAT_VERYVERBOSE(FString::Printf(TEXT("process captured %d frames without resampling"), frameCount));

                    this->EmbeddedVoiceChatDevice->processAudio(firstChannelAudioData, frameCount);
                }
                
                free(firstChannelAudioData);
            }
#endif

            OnGeneratedAudio((const float *)AudioData, NumFrames * InNumChannels);
        };

        Audio::FCaptureDeviceInfo Info;
        if (!AudioCapture.GetCaptureDeviceInfo(Info)) {
            return false;
        }

        // Start the stream here to avoid hitching the audio render thread.
        Audio::FAudioCaptureDeviceParams Params;
        Params.DeviceIndex = DeviceIndex;
        Params.bUseHardwareAEC = Info.bSupportsHardwareAEC;
        if (AudioCapture.OpenAudioCaptureStream(Params, MoveTemp(OnCapture), NumFramesDesired)) {
            // If we opened the capture stream successfully, get the capture device info and initialize the UAudioGenerator
            Init(Info.PreferredSampleRate, Info.InputChannels);

#if WITH_EMBEDDEDVOICECHAT
            if (AudioCapture.GetSampleRate() != 0 && AudioCapture.GetSampleRate() != EmbeddedVoiceChat::sampleRate) {
                Resampler.Init(Audio::EResamplingMethod::Linear, EmbeddedVoiceChat::sampleRate / AudioCapture.GetSampleRate(), 1);
            }
#endif

            return true;
        }
    }
    return false;
}

bool UEmbeddedVoiceChatAudioCapture::CloseStream() {
    if (AudioCapture.IsStreamOpen()) {
        return AudioCapture.CloseStream();
    }

    return false;
}

void UEmbeddedVoiceChatAudioCapture::StartCapturingAudio() {
    if (AudioCapture.IsStreamOpen()) {
#if WITH_EMBEDDEDVOICECHAT
        if (this->EmbeddedVoiceChatDevice) {
            this->EmbeddedVoiceChatDevice->start();
        }
#endif
        AudioCapture.StartStream();
    }
}

void UEmbeddedVoiceChatAudioCapture::StopCapturingAudio() {
    if (AudioCapture.IsStreamOpen()) {
#if WITH_EMBEDDEDVOICECHAT
        if (this->EmbeddedVoiceChatDevice) {
            this->EmbeddedVoiceChatDevice->stop();
        }
#endif
        AudioCapture.StopStream();
    }
}

bool UEmbeddedVoiceChatAudioCapture::IsCapturingAudio() {
    return AudioCapture.IsCapturing();
}

bool UEmbeddedVoiceChatAudioCapture::IsTalking() {
#if WITH_EMBEDDEDVOICECHAT
	if (this->EmbeddedVoiceChatDevice) {
		return this->EmbeddedVoiceChatDevice->isTalking();
	}
#endif
    return false;
}
