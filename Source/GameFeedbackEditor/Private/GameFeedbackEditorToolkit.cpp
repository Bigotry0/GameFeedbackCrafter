// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFeedbackEditorToolkit.h"

#define LOCTEXT_NAMESPACE "FGameFeedbackEditorToolkit"

FName FGameFeedbackEditorToolkit::GetToolkitFName() const
{
	return FName(TEXT("GameFeedback"));
}

FText FGameFeedbackEditorToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("GameFeedbackEditorAppLabel", "GameFeedback Editor");
}

FString FGameFeedbackEditorToolkit::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("GameFeedbackTabPrefix", "GameFeedbackPrefix").ToString();
}

FLinearColor FGameFeedbackEditorToolkit::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}

#undef LOCTEXT_NAMESPACE
