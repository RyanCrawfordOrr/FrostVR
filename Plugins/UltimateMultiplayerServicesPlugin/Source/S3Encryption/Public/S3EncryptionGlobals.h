/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Written by Siqi.Wu <lion547016@gmail.com>, December 2018
 */

#pragma once

#define CURRENT_CLASS								(FString(__FUNCTION__).Left(FString(__FUNCTION__).Find(TEXT(":"))) )
#define CURRENT_CLASS_FUNCTION							(FString(__FUNCTION__))
#define CURRENT_FUNCTION							(FString(__FUNCTION__).Right(FString(__FUNCTION__).Len() - FString(__FUNCTION__).Find(TEXT("::")) ))
#define CURRENT_LINE_NUMBER							(FString::FromInt(__LINE__))
#define CURRENT_CLASS_WITH_LINE							("(" + CURRENT_LINE_NUMBER + ") " + CURRENT_CLASS)
#define CURRENT_FUNCTION_SIGNATURE						(FString(__FUNCSIG__))

#define NETMODE_WORLD (((GEngine == nullptr) || (GetWorld() == nullptr)) ? TEXT("[UNKNOWN_NETMODE] ") \
		: (GEngine->GetNetMode(GetWorld()) == NM_Client) ? TEXT("[Client] ") \
		: (GEngine->GetNetMode(GetWorld()) == NM_ListenServer) ? TEXT("[ListenServer] ") \
		: (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer) ? TEXT("[DedicatedServer] ") \
		: TEXT("[Standalone] "))

#define DEFINE_LOG(LogCategory)							DEFINE_LOG_CATEGORY_STATIC(LogCategory, All, All)

DEFINE_LOG(LogS3Encryption)

#define CREATE_S3ENCRYPTION_LOG_NORMAL(LogCategory, Param1)	   		UE_LOG(LogCategory, Log, TEXT("[%s::%s] %s"), *CURRENT_CLASS, *CURRENT_FUNCTION, *FString(Param1))
#define CREATE_S3ENCRYPTION_LOG_VERBOSE(LogCategory, Param1)	   	UE_LOG(LogCategory, Verbose, TEXT("[%s::%s] %s"), *CURRENT_CLASS, *CURRENT_FUNCTION, *FString(Param1))
#define CREATE_S3ENCRYPTION_LOG_VERYVERBOSE(LogCategory, Param1)	UE_LOG(LogCategory, VeryVerbose, TEXT("[%s::%s] %s"), *CURRENT_CLASS, *CURRENT_FUNCTION, *FString(Param1))
#define CREATE_S3ENCRYPTION_LOG_WARNING(LogCategory, Param1)   		UE_LOG(LogCategory, Warning, TEXT("[%s::%s] %s"), *CURRENT_CLASS, *CURRENT_FUNCTION, *FString(Param1))
#define CREATE_S3ENCRYPTION_LOG_ERROR(LogCategory, Param1)	   		UE_LOG(LogCategory, Error, TEXT("[%s::%s] %s"), *CURRENT_CLASS, *CURRENT_FUNCTION, *FString(Param1))

#define LOG_S3ENCRYPTION_NORMAL(Param1)	   							CREATE_S3ENCRYPTION_LOG_NORMAL(LogS3Encryption, Param1)
#define LOG_S3ENCRYPTION_VERBOSE(Param1)	   						CREATE_S3ENCRYPTION_LOG_VERBOSE(LogS3Encryption, Param1)
#define LOG_S3ENCRYPTION_VERYVERBOSE(Param1)						CREATE_S3ENCRYPTION_LOG_VERYVERBOSE(LogS3Encryption, Param1)
#define LOG_S3ENCRYPTION_WARNING(Param1)	   						CREATE_S3ENCRYPTION_LOG_WARNING(LogS3Encryption, Param1)
#define LOG_S3ENCRYPTION_ERROR(Param1)	   							CREATE_S3ENCRYPTION_LOG_ERROR(LogS3Encryption, Param1)
