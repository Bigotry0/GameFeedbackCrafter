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
class GAMEFEEDBACKCORE_API UGameFeedbackPlayer : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

private:
	bool bIsRunning = false;

	bool bAutoUnload = false;

	UPROPERTY()
	UGameFeedback* CurrentFeedback = nullptr;

	UFUNCTION()
	void OnGameFeedbackStateChanged(EGameFeedbackState NewState);

	UFUNCTION()
	void OnGameFeedbackStopped(bool bInterrupted);

public:
	UFUNCTION(BlueprintCallable, Category = "GameFeedbackPlayer")
	void LoadFeedback(UGameFeedback* Feedback);

	UFUNCTION(BlueprintCallable, Category = "GameFeedbackPlayer")
	void PlayFeedback(bool bUseAutoUnload = false);

	UFUNCTION(BlueprintCallable, Category = "GameFeedbackPlayer")
	void PauseFeedback() const;

	UFUNCTION(BlueprintCallable, Category = "GameFeedbackPlayer")
	void ResumeFeedback() const;

	UFUNCTION(BlueprintCallable, Category = "GameFeedbackPlayer")
	void StopFeedback() const;

	UFUNCTION(BlueprintCallable, Category = "GameFeedbackPlayer")
	void ReplayFeedback() const;

	UFUNCTION(BlueprintCallable, Category = "GameFeedbackPlayer")
	void UnloadFeedback();

protected:
	virtual TStatId GetStatId() const override;
	virtual void Tick(float DeltaTime) override;
};
