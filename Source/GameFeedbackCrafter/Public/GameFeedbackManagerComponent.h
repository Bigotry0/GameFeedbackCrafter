// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "GameFeedback.h"
#include "GameFeedbackPlayer.h"
#include "Components/ActorComponent.h"
#include "GameFeedbackManagerComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogGameFeedbackCrafter, Log, All);

UCLASS(ClassGroup=(GameFeedbackCrafter), meta=(BlueprintSpawnableComponent))
class GAMEFEEDBACKCRAFTER_API UGameFeedbackManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGameFeedbackManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Instanced, Category = "GameFeedbackManager")
	TMap<FName, UGameFeedback*> Feedbacks;

private:
	UPROPERTY()
	TMap<FName, UGameFeedbackPlayer*> FeedbackPlayers;

private:
	bool ValidateFeedback(FName FeedbackName) const;

	UGameFeedbackPlayer* GetFeedbackPlayerFromFeedbacksMap(FName FeedbackName);

public:
	UFUNCTION(BlueprintCallable, Category = "GameFeedbackManager")
	void PlayFeedback(FName FeedbackName);

	UFUNCTION(BlueprintCallable, Category = "GameFeedbackManager")
	void PauseFeedback(FName FeedbackName);

	UFUNCTION(BlueprintCallable, Category = "GameFeedbackManager")
	void ResumeFeedback(FName FeedbackName);

	UFUNCTION(BlueprintCallable, Category = "GameFeedbackManager")
	void StopFeedback(FName FeedbackName);

	UFUNCTION(BlueprintCallable, Category = "GameFeedbackManager")
	void ReplayFeedback(FName FeedbackName);

#if WITH_EDITORONLY_DATA

protected:
	UPROPERTY(EditAnywhere, Category = "GameFeedbackManagerDebug", meta = (DisplayName = "Debug Feedback Name"))
	FName DebugFeedbackName;

	UFUNCTION(CallInEditor, Category = "GameFeedbackManagerDebug", meta = (DisplayName = "Play Feedback"))
	void PlayFeedback_Debug()
	{
		if (ValidateFeedback(DebugFeedbackName))
		{
			PlayFeedback(DebugFeedbackName);
		}
	}

	UFUNCTION(CallInEditor, Category = "GameFeedbackManagerDebug", meta = (DisplayName = "Pause Feedback"))
	void PauseFeedback_Debug()
	{
		if (ValidateFeedback(DebugFeedbackName))
		{
			PauseFeedback(DebugFeedbackName);
		}
	}

	UFUNCTION(CallInEditor, Category = "GameFeedbackManagerDebug", meta = (DisplayName = "Resume Feedback"))
	void ResumeFeedback_Debug()
	{
		if (ValidateFeedback(DebugFeedbackName))
		{
			ResumeFeedback(DebugFeedbackName);
		}
	}

	UFUNCTION(CallInEditor, Category = "GameFeedbackManagerDebug", meta = (DisplayName = "Stop Feedback"))
	void StopFeedback_Debug()
	{
		if (ValidateFeedback(DebugFeedbackName))
		{
			StopFeedback(DebugFeedbackName);
		}
	}

	UFUNCTION(CallInEditor, Category = "GameFeedbackManagerDebug", meta = (DisplayName = "Replay Feedback"))
	void ReplayFeedback_Debug()
	{
		if (ValidateFeedback(DebugFeedbackName))
		{
			ReplayFeedback(DebugFeedbackName);
		}
	}

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;


#endif
};
