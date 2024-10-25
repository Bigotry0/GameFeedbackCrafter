// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "GameFeedbackEffectBase.generated.h"

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
	GENERATED_BODY()

	virtual ~FGameFeedbackEffectBase() = default;

private:
	float ElapsedTime = 0.0f;

public:
	UPROPERTY(EditAnywhere)
	float Duration = 0.2f;

	UPROPERTY(VisibleAnywhere)
	EGameFeedbackEffectState State = EGameFeedbackEffectState::NotInitialized;

	void Init();

	void Play();

	void Pause();

	void Resume();

	void Stop();

	bool Tick(float DeltaTime);

protected:
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

	virtual void OnTick(float DeltaTime)
	{
	}
};
