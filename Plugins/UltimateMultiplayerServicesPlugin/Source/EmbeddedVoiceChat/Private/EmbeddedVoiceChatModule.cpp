/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Written by Siqi.Wu <lion547016@gmail.com>, Feb 2022
 */

#include "EmbeddedVoiceChatModule.h"
#include "EmbeddedVoiceChatPrivatePCH.h"
#include "EmbeddedVoiceChatGlobals.h"
#include "UnrealEmbeddedVoiceChatLogInterface.h"
#include "Interfaces/IPluginManager.h"

#include "Misc/ConfigCacheIni.h"

#if PLATFORM_IOS
#include "IOS/IOSAppDelegate.h"
#endif

#if WITH_EMBEDDEDVOICECHAT
std::shared_ptr<EmbeddedVoiceChat::LogInterface> FEmbeddedVoiceChatModule::logInterface = std::make_shared<UnrealEmbeddedVoiceChatLogInterface>();
#endif

#define LOCTEXT_NAMESPACE "FEmbeddedVoiceChatModule"

void FEmbeddedVoiceChatModule::StartupModule()
{
    LLM_SCOPE(ELLMTag::Audio);
    // Load platform specific implementations for audio capture (if specified in a .ini file)
    FString AudioCaptureModuleName;
    if (GConfig->GetString(TEXT("Audio"), TEXT("AudioCaptureModuleName"), AudioCaptureModuleName, GEngineIni)) {
        FModuleManager::Get().LoadModule(*AudioCaptureModuleName);
    } else {
#if PLATFORM_WINDOWS || PLATFORM_MAC
        FModuleManager::Get().LoadModule(TEXT("AudioCaptureRtAudio"));
#elif PLATFORM_IOS
        FModuleManager::Get().LoadModule(TEXT("AudioCaptureAudioUnit"));
#elif PLATFORM_ANDROID
        FModuleManager::Get().LoadModule(TEXT("AudioCaptureAndroid"));
#endif
    }

    {
#if PLATFORM_WINDOWS
        FModuleManager::Get().LoadModule(TEXT("AudioMixerXAudio2"));
#elif PLATFORM_MAC
        FModuleManager::Get().LoadModule(TEXT("AudioMixerCoreAudio"));
#elif PLATFORM_IOS
        FModuleManager::Get().LoadModule(TEXT("AudioMixerAudioUnit"));
#elif PLATFORM_ANDROID
        FModuleManager::Get().LoadModule(TEXT("AudioMixerAndroid"));
#elif PLATFORM_LINUX || PLATFORM_LINUXARM64
        FModuleManager::Get().LoadModule(TEXT("AudioMixerSDL"));
#endif
    }

#if PLATFORM_IOS
    [[IOSAppDelegate GetDelegate] EnableHighQualityVoiceChat:true];
    [[IOSAppDelegate GetDelegate] EnableVoiceChat:true];
#endif

#if WITH_EMBEDDEDVOICECHAT
#if PLATFORM_WINDOWS && PLATFORM_64BITS
	LOG_EMBEDDEDVOICECHAT_NORMAL("Starting Embedded Voice Chat Module...");
#elif PLATFORM_MAC
    LOG_EMBEDDEDVOICECHAT_NORMAL("Starting Embedded Voice Chat Module...");
#elif PLATFORM_IOS
	LOG_EMBEDDEDVOICECHAT_NORMAL("Starting Embedded Voice Chat Module...");
#endif
    EmbeddedVoiceChat::logInterface = FEmbeddedVoiceChatModule::logInterface;
#endif
}

void FEmbeddedVoiceChatModule::ShutdownModule()
{
#if PLATFORM_IOS
    [[IOSAppDelegate GetDelegate] EnableHighQualityVoiceChat:false];
    [[IOSAppDelegate GetDelegate] EnableVoiceChat:false];
#endif
#if WITH_EMBEDDEDVOICECHAT
    FEmbeddedVoiceChatModule::logInterface = nullptr;
#if PLATFORM_MAC
#endif
#endif

	LOG_EMBEDDEDVOICECHAT_NORMAL("Shutting down Embedded Voice Chat Module...");
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEmbeddedVoiceChatModule, EmbeddedVoiceChat);
