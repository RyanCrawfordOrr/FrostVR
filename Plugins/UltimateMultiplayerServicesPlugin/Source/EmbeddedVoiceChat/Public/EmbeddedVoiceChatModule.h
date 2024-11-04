/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Written by Siqi.Wu <lion547016@gmail.com>, Feb 2022
 */

#pragma once

#include "Modules/ModuleManager.h"

#if WITH_EMBEDDEDVOICECHAT
#endif

class FEmbeddedVoiceChatModule : public IModuleInterface
{
public:
	void StartupModule();
	void ShutdownModule();

private:
#if WITH_EMBEDDEDVOICECHAT
    static std::shared_ptr<EmbeddedVoiceChat::LogInterface> logInterface;
#endif
};
