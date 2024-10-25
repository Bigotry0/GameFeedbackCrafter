// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EGameFeedbackEffectState : uint8
{
	NotInitialized,
	Idle,
	Running,
	Paused,
};

USTRUCT(BlueprintType)
struct FGameFeedbackEffectBase
{
protected:
	~FGameFeedbackEffectBase() = default;

public:
	UPROPERTY(EditAnywhere)
	float Duration = 0.2f;

	UPROPERTY(VisibleAnywhere)
	EGameFeedbackEffectState State = EGameFeedbackEffectState::NotInitialized;

	// Life cycle
	virtual void OnInit()
	{
	}

	virtual void OnPlay()
	{
	}

	virtual void OnPause()
	{
	}

	virtual void OnResume()
	{
	}

	virtual void OnStop(bool bInterrupted)
	{
	}
};
