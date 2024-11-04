/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Written by Siqi.Wu <lion547016@gmail.com>, September 2020
 */

#include "CloudWatchLogsModule.h"
#include "CloudWatchLogsGlobals.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

#if WITH_EDITOR
#include "Misc/Paths.h"
#include "Misc/MessageDialog.h"
#include "HAL/PlatformProcess.h"
#endif

#define LOCTEXT_NAMESPACE "FCloudWatchLogsModule"

#if WITH_EDITOR
void* FCloudWatchLogsModule::CloudWatchLogsLibraryHandle = nullptr;
#endif

void FCloudWatchLogsModule::StartupModule()
{
    LOG_CLOUDWATCHLOGS_NORMAL("Starting CloudWatchLogsClient Module...");
#if WITH_EDITOR
#if PLATFORM_WINDOWS && PLATFORM_64BITS
	const FString BaseDir = IPluginManager::Get().FindPlugin("awsSDK")->GetBaseDir();
	LOG_CLOUDWATCHLOGS_NORMAL(FString::Printf(TEXT("Base directory is %s"), *BaseDir));

	const FString ThirdPartyDir = FPaths::Combine(*BaseDir, TEXT("Source"), TEXT("ThirdParty"), TEXT("CloudWatchLogsClientLibrary"), TEXT("Win64"),  TEXT("Editor"));
	LOG_CLOUDWATCHLOGS_NORMAL(FString::Printf(TEXT("ThirdParty directory is %s"), *ThirdPartyDir));

	static const FString CloudWatchLogsDLLName = "aws-cpp-sdk-logs";
	const bool bDependencyLoaded = LoadDependency(ThirdPartyDir, CloudWatchLogsDLLName, CloudWatchLogsLibraryHandle);
	if (!bDependencyLoaded)
	{
		FFormatNamedArguments Arguments;
		Arguments.Add(TEXT("Name"), FText::FromString(CloudWatchLogsDLLName));
		FMessageDialog::Open(EAppMsgType::Ok, FText::Format(LOCTEXT("LoadDependencyError", "Failed to load {Name}."), Arguments));
		FreeDependency(CloudWatchLogsLibraryHandle);
	}
#elif PLATFORM_MAC
	LOG_CLOUDWATCHLOGS_NORMAL("Starting CloudWatchLogsClient Module...");
    const FString BaseDir = IPluginManager::Get().FindPlugin("awsSDK")->GetBaseDir();
    LOG_CLOUDWATCHLOGS_NORMAL(FString::Printf(TEXT("Base directory is %s"), *BaseDir));

    const FString ThirdPartyDir = FPaths::Combine(*BaseDir, TEXT("Source"), TEXT("ThirdParty"), TEXT("CloudWatchLogsClientLibrary"), TEXT("Mac"),  TEXT("Editor"));
    LOG_CLOUDWATCHLOGS_NORMAL(FString::Printf(TEXT("ThirdParty directory is %s"), *ThirdPartyDir));

    static const FString CloudWatchLogsDLLName = "libaws-cpp-sdk-logs";
    const bool bDependencyLoaded = LoadDependency(ThirdPartyDir, CloudWatchLogsDLLName, CloudWatchLogsLibraryHandle);
    if (!bDependencyLoaded)
    {
        FFormatNamedArguments Arguments;
        Arguments.Add(TEXT("Name"), FText::FromString(CloudWatchLogsDLLName));
        FMessageDialog::Open(EAppMsgType::Ok, FText::Format(LOCTEXT("LoadDependencyError", "Failed to load {Name}."), Arguments));
        FreeDependency(CloudWatchLogsLibraryHandle);
    }
#elif PLATFORM_IOS
#endif
#endif
}

void FCloudWatchLogsModule::ShutdownModule()
{
#if WITH_EDITOR
	FreeDependency(CloudWatchLogsLibraryHandle);
#endif
	LOG_CLOUDWATCHLOGS_NORMAL("Shutting down CloudWatchLogs Module...");
}

#if WITH_EDITOR
bool FCloudWatchLogsModule::LoadDependency(const FString& Dir, const FString& Name, void*& Handle)
{
	FString Lib = Name + TEXT(".") + FPlatformProcess::GetModuleExtension();
	FString Path = Dir.IsEmpty() ? *Lib : FPaths::Combine(*Dir, *Lib);

	Handle = FPlatformProcess::GetDllHandle(*Path);

	if (Handle == nullptr)
	{
		LOG_CLOUDWATCHLOGS_ERROR(FString::Printf(TEXT("Dependency %s failed to load in directory %s"), *Lib, *Dir));
		return false;
	}

	LOG_CLOUDWATCHLOGS_NORMAL(FString::Printf(TEXT("Dependency %s successfully loaded from directory %s"), *Lib, *Dir));
	return true;
}

void FCloudWatchLogsModule::FreeDependency(void*& Handle)
{
#if !PLATFORM_LINUX && !PLATFORM_ANDROID && !PLATFORM_IOS
	if (Handle != nullptr)
	{
		FPlatformProcess::FreeDllHandle(Handle);
		Handle = nullptr;
	}
#endif
}
#endif

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCloudWatchLogsModule, CloudWatchLogs)
