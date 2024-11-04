/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Written by Siqi.Wu <lion547016@gmail.com>, July 2021
 */

#pragma once

#ifdef _MSC_VER
//disable windows complaining about max template size.
    #pragma warning (disable : 4503)
#endif // _MSC_VER

#if defined (USE_WINDOWS_DLL_SEMANTICS) || defined (_WIN32)
    #ifdef _MSC_VER
        #pragma warning(disable : 4251)
    #endif // _MSC_VER

    #ifdef EMBEDDED_VOICE_CHAT_USE_IMPORT_EXPORT
        #ifdef EMBEDDED_VOICE_CHAT_EXPORTS
            #define EMBEDDED_VOICE_CHAT_API __declspec(dllexport)
        #else
            #define EMBEDDED_VOICE_CHAT_API __declspec(dllimport)
        #endif /* EMBEDDED_VOICE_CHAT_EXPORTS */
    #else
        #define EMBEDDED_VOICE_CHAT_API
    #endif // EMBEDDED_VOICE_CHAT_USE_IMPORT_EXPORT
#else // defined (USE_WINDOWS_DLL_SEMANTICS) || defined (WIN32)
    #define EMBEDDED_VOICE_CHAT_API
#endif // defined (USE_WINDOWS_DLL_SEMANTICS) || defined (WIN32)
