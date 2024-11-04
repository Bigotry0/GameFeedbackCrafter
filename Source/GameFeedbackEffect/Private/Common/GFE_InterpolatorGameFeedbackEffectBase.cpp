// Copyright (c) Lim Young


#include "Common/GFE_InterpolatorGameFeedbackEffectBase.h"

void UGFE_InterpolatorGameFeedbackEffectBase::OnInit()
{
	Super::OnInit();

	Interpolator.UpdateAlpha(0);
}

void UGFE_InterpolatorGameFeedbackEffectBase::OnStop(bool bInterrupted)
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

void UGFE_InterpolatorGameFeedbackEffectBase::OnTick(float DeltaTime)
{
	Super::OnTick(DeltaTime);

	Interpolator.UpdateAlpha(GetEffectProgress());
}

float UGFE_InterpolatorGameFeedbackEffectBase::GetInterpolatorAlpha() const
{
	return Interpolator.GetAlpha();
}
