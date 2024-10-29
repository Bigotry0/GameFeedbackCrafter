// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "GameFeedbackEffectBase.h"
#include "Util/GFUtilStruct.h"
#include "InterpolatorGameFeedbackEffectBase.generated.h"

/**
 * Maintains a GFInterpolator instance and updates it with the progress of the effect.
 * Implementations should call GetInterpolatorAlpha() to get the current alpha value.
 */
UCLASS(Abstract)
class GAMEFEEDBACKEFFECT_API UInterpolatorGameFeedbackEffectBase : public UGameFeedbackEffectBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Interpolator")
	FGFInterpolator Interpolator;

protected:
	virtual void OnInit() override;
	virtual void OnStop(bool bInterrupted) override;
	virtual void OnTick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintCallable, Category = "GameFeedbackEffect")
	float GetInterpolatorAlpha() const;
};
