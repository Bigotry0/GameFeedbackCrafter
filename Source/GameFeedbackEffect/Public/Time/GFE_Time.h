// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "GameFeedbackEffectBase.h"
#include "Common/GFE_InterpolatorGameFeedbackEffectBase.h"
#include "GFE_Time.generated.h"


/**
 * Freezes the game for a short period of time.
 * Can quickly create a slow-motion effect.
 */
UCLASS()
class UGFE_Time_FreezeFrame : public UGameFeedbackEffectBase
{
	GENERATED_BODY()

public:
	/**
	 * The time dilation value to apply during the freeze-frame effect.
	 */
	UPROPERTY(EditAnywhere, Category = "Time")
	float MinimumTimeDilation = 0.1f;

private:
	float OriginalTimeDilation = 1.0f;

	UPROPERTY()
	UWorld* ContextWorld = nullptr;

protected:
	virtual void OnInit() override;
	virtual void OnPlay() override;
	virtual void OnStop(bool bInterrupted) override;

#if WITH_EDITOR
	virtual EGameFeedbackEffectType GetEffectType() const override
	{
		return EGameFeedbackEffectType::Time;
	}
#endif
};

/**
 * Interpolates the global time dilation value over time.
 * Can be used to create a smooth transition between time dilation values.
 * This effect is potentially useful for creating some kind of time manipulation effect.
 */
UCLASS()
class UGFE_Time_TimeFollow : public UGFE_InterpolatorGameFeedbackEffectBase
{
	GENERATED_BODY()

public:
	/**
	 * Time dilation coefficients for interpolated starting points
	 */
	UPROPERTY(EditAnywhere, Category = "Time")
	float StartTimeDilation = 0.1f;

	/**
	 * Time dilation coefficients for interpolated ending points
	 */
	UPROPERTY(EditAnywhere, Category = "Time")
	float EndTimeDilation = 1.0f;

	/**
	 * Force time dilation to EndTimeDilation when interrupted
	 */
	UPROPERTY(EditAnywhere, Category = "Time")
	bool bForceEndTimeDilationWhenInterrupted = false;

private:
	UPROPERTY()
	UWorld* ContextWorld = nullptr;

protected:
	virtual void OnInit() override;
	virtual void OnPlay() override;
	virtual void OnTick(float DeltaTime) override;
	virtual void OnStop(bool bInterrupted) override;

#if WITH_EDITOR
	virtual EGameFeedbackEffectType GetEffectType() const override
	{
		return EGameFeedbackEffectType::Time;
	}
#endif
};
