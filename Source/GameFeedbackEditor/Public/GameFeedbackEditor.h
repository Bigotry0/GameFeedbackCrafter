// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "GameFeedbackAssetTypeActions.h"
#include "Modules/ModuleManager.h"

class FGameFeedbackEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedPtr<FGameFeedbackAssetTypeActions> GameFeedbackAssetTypeActions;
};
