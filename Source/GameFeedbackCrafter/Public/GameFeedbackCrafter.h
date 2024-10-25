// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FGameFeedbackCrafterModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
