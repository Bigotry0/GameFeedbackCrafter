// Copyright (c) Lim Young

#include "GameFeedbackEffectBase.h"

void UGameFeedbackEffectBase::Init()
{
	ElapsedTime = 0.0f;

	OnInit();

	State = EGameFeedbackEffectState::Idle;
}

void UGameFeedbackEffectBase::Play()
{
	OnPlay();

	State = EGameFeedbackEffectState::Running;
}

void UGameFeedbackEffectBase::Pause()
{
	OnPause();

	State = EGameFeedbackEffectState::Paused;
}

void UGameFeedbackEffectBase::Resume()
{
	OnResume();

	State = EGameFeedbackEffectState::Running;
}

void UGameFeedbackEffectBase::Stop()
{
	if (State == EGameFeedbackEffectState::Running || State == EGameFeedbackEffectState::Paused)
	{
		OnStop(true);
	}

	ElapsedTime = 0.0f;

	State = EGameFeedbackEffectState::Idle;
}

bool UGameFeedbackEffectBase::Tick(float DeltaTime)
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
