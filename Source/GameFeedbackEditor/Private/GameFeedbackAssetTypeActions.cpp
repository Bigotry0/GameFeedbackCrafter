// Copyright (c) Lim Young


#include "GameFeedbackAssetTypeActions.h"

#include "GameFeedback.h"


UClass* FGameFeedbackAssetTypeActions::GetSupportedClass() const
{
	return UGameFeedback::StaticClass();
}

FText FGameFeedbackAssetTypeActions::GetName() const
{
	return INVTEXT("Game Feedback");
}

FColor FGameFeedbackAssetTypeActions::GetTypeColor() const
{
	return FColor(54, 186, 152);
}

uint32 FGameFeedbackAssetTypeActions::GetCategories()
{
	// 注册自定义分类
	return FAssetToolsModule::GetModule().Get().RegisterAdvancedAssetCategory(
		FName(TEXT("GameFeedback")), INVTEXT("Game Feedback"));
}
