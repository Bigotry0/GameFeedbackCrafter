﻿// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FGameFeedbackCoreModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
