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

	Interpolator.UpdateAlpha(GetEffectProgress());
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
