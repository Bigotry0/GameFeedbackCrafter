// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameFeedbackEffectBase.generated.h"

UENUM(BlueprintType)
enum class EGameFeedbackEffectState : uint8
{
	NotInitialized,
	Idle,
	Running,
	Paused,
};

UCLASS(Abstract, EditInlineNew, AutoExpandCategories=(Basic))
class GAMEFEEDBACKCORE_API UGameFeedbackEffectBase : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category = "Basic")
	float ElapsedTime = 0.0f;

public:
	UPROPERTY(EditAnywhere, Category = "Basic")
	float Duration = 0.2f;

	UPROPERTY(VisibleAnywhere, Category = "Basic")
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
