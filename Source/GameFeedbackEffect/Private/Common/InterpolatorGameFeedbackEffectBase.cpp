// Copyright (c) Lim Young


#include "Common/InterpolatorGameFeedbackEffectBase.h"

void UInterpolatorGameFeedbackEffectBase::OnInit()
{
	Super::OnInit();

	Interpolator.UpdateAlpha(0);
}

void UInterpolatorGameFeedbackEffectBase::OnStop(bool bInterrupted)
{
	Super::OnStop(bInterrupted);

	if (bInterrupted)
	{
		Interpolator.UpdateAlpha(GetEffectProgress());
	}
	else
	{
		Interpolator.UpdateAlpha(1);
	}
}

void UInterpolatorGameFeedbackEffectBase::OnTick(float DeltaTime)
{
	Super::OnTick(DeltaTime);

	Interpolator.UpdateAlpha(GetEffectProgress());
}

float UInterpolatorGameFeedbackEffectBase::GetInterpolatorAlpha() const
{
	return Interpolator.GetAlpha();
}
