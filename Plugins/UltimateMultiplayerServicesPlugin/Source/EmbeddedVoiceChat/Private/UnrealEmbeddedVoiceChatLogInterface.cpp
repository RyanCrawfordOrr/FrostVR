/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Written by Siqi.Wu <lion547016@gmail.com>, Feb 2022
 */

#include "UnrealEmbeddedVoiceChatLogInterface.h"

#include "EmbeddedVoiceChatGlobals.h"

#if WITH_EMBEDDEDVOICECHAT
#include <sstream>
#include <cstdarg>
#include <stdio.h>
#include <thread>

void UnrealEmbeddedVoiceChatLogInterface::Log(EmbeddedVoiceChat::LogLevel logLevel, const char* tag, const char* formatStr, ...)
{
    std::stringstream ss;
    ss << tag << " [" << std::this_thread::get_id() << "] ";

    std::va_list args;
    va_start(args, formatStr);

    va_list tmp_args; //unfortunately you cannot consume a va_list twice
    va_copy(tmp_args, args); //so we have to copy it
    #ifdef WIN32
        const int requiredLength = _vscprintf(formatStr, tmp_args) + 1;
    #else
        const int requiredLength = vsnprintf(nullptr, 0, formatStr, tmp_args) + 1;
    #endif
    va_end(tmp_args);

    char *outputBuff = (char *)malloc(requiredLength);
    #ifdef WIN32
        vsnprintf_s(outputBuff, requiredLength, _TRUNCATE, formatStr, args);
    #else
        vsnprintf(outputBuff, requiredLength, formatStr, args);
    #endif // WIN32

    ss << outputBuff << std::endl;
  
    switch(logLevel) {
        case EmbeddedVoiceChat::LogLevel::None:
            break;
        case EmbeddedVoiceChat::LogLevel::Fatal:
            LOG_EMBEDDEDVOICECHAT_ERROR(UTF8_TO_TCHAR(ss.str().c_str()));
            break;
        case EmbeddedVoiceChat::LogLevel::Error:
            LOG_EMBEDDEDVOICECHAT_ERROR(UTF8_TO_TCHAR(ss.str().c_str()));
            break;
        case EmbeddedVoiceChat::LogLevel::Warning:
            LOG_EMBEDDEDVOICECHAT_WARNING(UTF8_TO_TCHAR(ss.str().c_str()));
            break;
        case EmbeddedVoiceChat::LogLevel::Info:
            LOG_EMBEDDEDVOICECHAT_NORMAL(UTF8_TO_TCHAR(ss.str().c_str()));
            break;
        case EmbeddedVoiceChat::LogLevel::Debug:
            LOG_EMBEDDEDVOICECHAT_VERBOSE(UTF8_TO_TCHAR(ss.str().c_str()));
            break;
        case EmbeddedVoiceChat::LogLevel::Verbose:
            LOG_EMBEDDEDVOICECHAT_VERYVERBOSE(UTF8_TO_TCHAR(ss.str().c_str()));
            break;
    }
    free(outputBuff);

    va_end(args);
}
#endif
