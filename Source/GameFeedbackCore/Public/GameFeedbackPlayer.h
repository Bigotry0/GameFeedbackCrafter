// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "GameFeedback.h"
#include "UObject/Object.h"
#include "GameFeedbackPlayer.generated.h"

/**
 * 
 */
UCLASS()
class GAMEFEEDBACKCORE_API UGameFeedbackPlayer : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "GameFeedbackPlayer")
	void InitFeedback(UGameFeedback* Feedback);

	UFUNCTION(BlueprintCallable, Category = "GameFeedbackPlayer")
	void PlayFeedback(UGameFeedback* Feedback);

	UFUNCTION(BlueprintCallable, Category = "GameFeedbackPlayer")
	void PauseFeedback(UGameFeedback* Feedback);

	UFUNCTION(BlueprintCallable, Category = "GameFeedbackPlayer")
	void ResumeFeedback(UGameFeedback* Feedback);

	UFUNCTION(BlueprintCallable, Category = "GameFeedbackPlayer")
	void StopFeedback(UGameFeedback* Feedback);

	UFUNCTION(BlueprintCallable, Category = "GameFeedbackPlayer")
	void ReplayFeedback(UGameFeedback* Feedback);
};
