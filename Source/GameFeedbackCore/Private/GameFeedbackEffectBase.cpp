// Copyright (c) Lim Young

#include "GameFeedbackEffectBase.h"

void FGameFeedbackEffectBase::Init()
{
	ElapsedTime = 0.0f;

	OnInit();

	State = EGameFeedbackEffectState::Idle;
}

void FGameFeedbackEffectBase::Play()
{
	OnPlay();

	State = EGameFeedbackEffectState::Running;
}

void FGameFeedbackEffectBase::Pause()
{
	OnPlay();

	State = EGameFeedbackEffectState::Paused;
}

void FGameFeedbackEffectBase::Resume()
{
	OnResume();

	State = EGameFeedbackEffectState::Running;
}

void FGameFeedbackEffectBase::Stop()
{
	if (State == EGameFeedbackEffectState::Running || State == EGameFeedbackEffectState::Paused)
	{
		OnStop(true);
	}

	ElapsedTime = 0.0f;

	State = EGameFeedbackEffectState::Idle;
}

bool FGameFeedbackEffectBase::Tick(float DeltaTime)
{
	if (State == EGameFeedbackEffectState::Running)
	{
		OnTick(DeltaTime);

		ElapsedTime += DeltaTime;

		if (ElapsedTime >= Duration)
		{
			OnStop(false);

			ElapsedTime = 0.0f;

			State = EGameFeedbackEffectState::Idle;
		}

		return true;
	}

	return false;
}
