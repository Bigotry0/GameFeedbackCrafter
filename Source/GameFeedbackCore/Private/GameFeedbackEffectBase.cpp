// Copyright (c) Lim Young

#include "GameFeedbackEffectBase.h"

void UGameFeedbackEffectBase::Init()
{
	BasicConfig.ElapsedTime = 0.0f;

	OnInit();

	BasicConfig.State = EGameFeedbackEffectState::Idle;
}

void UGameFeedbackEffectBase::Play()
{
	OnPlay();

	BasicConfig.State = EGameFeedbackEffectState::Running;
}

void UGameFeedbackEffectBase::Pause()
{
	OnPause();

	BasicConfig.State = EGameFeedbackEffectState::Paused;
}

void UGameFeedbackEffectBase::Resume()
{
	OnResume();

	BasicConfig.State = EGameFeedbackEffectState::Running;
}

void UGameFeedbackEffectBase::Stop()
{
	if (BasicConfig.State == EGameFeedbackEffectState::Running || BasicConfig.State == EGameFeedbackEffectState::Paused)
	{
		OnStop(true);

		BasicConfig.ElapsedTime = 0.0f;

		BasicConfig.State = EGameFeedbackEffectState::Idle;
	}
}

bool UGameFeedbackEffectBase::Tick(float DeltaTime)
{
	if (BasicConfig.State == EGameFeedbackEffectState::Running)
	{
		OnTick(DeltaTime);

		BasicConfig.ElapsedTime += DeltaTime;

		if (BasicConfig.ElapsedTime >= BasicConfig.Duration)
		{
			OnStop(false);

			BasicConfig.ElapsedTime = 0.0f;

			BasicConfig.State = EGameFeedbackEffectState::Idle;
		}

		return true;
	}

	return false;
}
