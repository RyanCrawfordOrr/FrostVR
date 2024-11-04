/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, Jan 2023
*/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UObject/NoExportTypes.h"
#include "Generators/AudioGenerator.h"
#include "AudioCaptureCore.h"
#include "AudioResampler.h"

#if WITH_EMBEDDEDVOICECHAT

#include "EmbeddedVoiceChat/EmbeddedVoiceChatDevice.h"

#endif

#include "EmbeddedVoiceChatAudioCapture.generated.h"

// Struct defining the time synth global quantization settings
USTRUCT(BlueprintType)
struct EMBEDDEDVOICECHAT_API FEmbeddedVoiceChatAudioCaptureDeviceInfo {
    GENERATED_USTRUCT_BODY()

    // The name of the audio capture device
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AudioCapture")
    FName DeviceName;

    // The name of the audio capture device
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AudioCapture")
    FString DeviceId;

    // The number of input channels
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AudioCapture")
    int32 NumInputChannels = 0;

    // The sample rate of the audio capture device
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AudioCapture")
    int32 SampleRate = 0;

    // The sample rate of the audio capture device
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AudioCapture")
    bool bSupportsHardwareAEC = false;
};

// Class which opens up a handle to an audio capture device.
// Allows other objects to get audio buffers from the capture device.
// Based on unreal engine audio capture core.
// @TODO: sample rate and channel
UCLASS(BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EMBEDDEDVOICECHAT_API UEmbeddedVoiceChatAudioCapture : public UAudioGenerator {
    GENERATED_BODY()

public:
#if WITH_EMBEDDEDVOICECHAT
    std::shared_ptr<EmbeddedVoiceChat::AbstractCaptureDevice> EmbeddedVoiceChatDevice;
#endif

    UEmbeddedVoiceChatAudioCapture();
    ~UEmbeddedVoiceChatAudioCapture();

    // Returns the total amount of audio devices.
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    int32 GetCaptureDevicesAvailable(TArray<FEmbeddedVoiceChatAudioCaptureDeviceInfo>& OutDevices);

    // Returns the audio capture device information at the given Id.
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    bool GetCaptureDeviceInfo(FEmbeddedVoiceChatAudioCaptureDeviceInfo& OutInfo, int32 DeviceIndex = -1);

    // Opens the audio capture stream with the given parameters
    // @Param: DeviceIndex: 0 means default device.
    // @Param: NumFramesDesired: don't change it if you don't know what it is.
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    bool OpenCaptureStream(int32 DeviceIndex = -1, int32 NumFramesDesired = 480);

    // Closes the audio capture stream
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    bool CloseStream();

    // Starts capturing audio
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    void StartCapturingAudio();

    // Stops capturing audio
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    void StopCapturingAudio();

    // Returns true if capturing audio
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    bool IsCapturingAudio();

    // Returns true if capturing audio
    UFUNCTION(BlueprintCallable, Category = "Embedded Voice Chat")
    bool IsTalking();

protected:

    Audio::FAudioCapture AudioCapture;
    Audio::FResampler Resampler;
};
