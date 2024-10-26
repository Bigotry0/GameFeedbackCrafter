﻿// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "GameFeedbackEffectBase.h"
#include "UObject/Object.h"
#include "GameFeedback.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(GameFeedbackCoreLog, Log, All);

UENUM(BlueprintType)
enum class EGameFeedbackState : uint8
{
	NotInitialized,
	Idle,
	Running,
	Paused,
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, EditInlineNew)
class GAMEFEEDBACKCORE_API UGameFeedback : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Instanced, Category = "GameFeedback")
	TArray<UGameFeedbackEffectBase*> GameFeedbackEffects;

	UPROPERTY(VisibleAnywhere, Category = "GameFeedback")
	EGameFeedbackState State = EGameFeedbackState::NotInitialized;

	UPROPERTY(VisibleAnywhere, Category = "GameFeedback")
	float ElapsedTime = 0.0f;

public:
	bool NotInIdleState() const
	{
		return State != EGameFeedbackState::Idle;
	}

private:
	/**
	 * Validate GameFeedbackEffects
	 * @return true if valid 
	 */
	bool ValidateGameFeedbackEffects() const;

	/**
	 * Validate GameFeedbackEffect
	 * @param GameFeedbackEffect GameFeedbackEffectPtr
	 * @return true if valid
	 */
	static bool ValidateGameFeedbackEffect(const UGameFeedbackEffectBase* GameFeedbackEffect);

	void SetState(EGameFeedbackState NewState);

public:
	/**
	 * Init feedback
	 */
	void InitFeedback();

	/**
	 * Play feedback
	 */
	void PlayFeedback();

	/**
	 * Pause feedback
	 */
	void PauseFeedback();

	/**
	 * Resume feedback
	 */
	void ResumeFeedback();

	/**
	 * Stop feedback
	 */
	void StopFeedback();

	/**
	 * Tick feedback
	 * @param DeltaTime DeltaTime
	 */
	void TickFeedback(float DeltaTime);

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameFeedbackStateChanged, EGameFeedbackState, NewState);

	UPROPERTY(BlueprintAssignable, Category = "GameFeedback")
	FOnGameFeedbackStateChanged OnGameFeedbackStateChanged;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameFeedbackStopped, bool, bInterrupted);

	UPROPERTY(BlueprintAssignable, Category = "GameFeedback")
	FOnGameFeedbackStopped OnGameFeedbackStopped;
};
