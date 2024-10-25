// Copyright (c) Lim Young

#include "GameFeedbackEditor.h"

#define LOCTEXT_NAMESPACE "FGameFeedbackEditorModule"

void FGameFeedbackEditorModule::StartupModule()
{
	GameFeedbackAssetTypeActions = MakeShared<FGameFeedbackAssetTypeActions>();
	FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(GameFeedbackAssetTypeActions.ToSharedRef());
}

void FGameFeedbackEditorModule::ShutdownModule()
{
	if (!FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		return;
	}

	FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(GameFeedbackAssetTypeActions.ToSharedRef());
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FGameFeedbackEditorModule, GameFeedbackEditor)
