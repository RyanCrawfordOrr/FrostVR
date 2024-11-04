/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Written by Siqi.Wu <lion547016@gmail.com>, October 2020
 */
#include "GraphQLModule.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FGraphQLModule"

void FGraphQLModule::StartupModule()
{
    if(!FModuleManager::Get().IsModuleLoaded("WebSockets"))
    {
        FModuleManager::Get().LoadModule("WebSockets");
    }
    
    if(!FModuleManager::Get().IsModuleLoaded("HTTP"))
    {
        FModuleManager::Get().LoadModule("HTTP");
    }

    if(!FModuleManager::Get().IsModuleLoaded("OpenSSL"))
    {
        FModuleManager::Get().LoadModule("OpenSSL");
    }
}

void FGraphQLModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FGraphQLModule, GraphQL)
