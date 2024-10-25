// Copyright (c) Lim Young

#include "GameFeedback.h"

#include "GameFeedbackEffectBase.h"

DEFINE_LOG_CATEGORY(GameFeedbackCoreLog);

bool UGameFeedback::ValidateGameFeedbackEffects() const
{
	if (GameFeedbackEffects.Num() <= 0)
	{
#if WITH_EDITOR
		UE_LOG(GameFeedbackCoreLog, Warning, TEXT("GameFeedbackEffects is empty."));
#endif
		return false;
	}

	return true;
}

bool UGameFeedback::ValidateGameFeedbackEffect(const FInstancedStruct& InstancedStruct)
{
	if (!InstancedStruct.IsValid())
	{
#if WITH_EDITOR
		UE_LOG(GameFeedbackCoreLog, Warning, TEXT("InstancedStruct is invalid."));
#endif
		return false;
	}

	return true;
}

void UGameFeedback::SetState(const EGameFeedbackState NewState)
{
	if (State != NewState)
	{
		State = NewState;
		OnGameFeedbackStateChanged.Broadcast(State);
	}
}

void UGameFeedback::InitFeedback()
{
	if (!ValidateGameFeedbackEffects())
	{
		return;
	}

	ElapsedTime = 0.0f;

	for (auto InstancedStruct : GameFeedbackEffects)
	{
		if (!ValidateGameFeedbackEffect(InstancedStruct))
			continue;

		InstancedStruct.GetMutable<FGameFeedbackEffectBase>().Init();
	}

	SetState(EGameFeedbackState::Idle);
}

void UGameFeedback::PlayFeedback()
{
	if (!ValidateGameFeedbackEffects())
	{
		return;
	}

	for (auto InstancedStruct : GameFeedbackEffects)
	{
		if (!ValidateGameFeedbackEffect(InstancedStruct))
			continue;

		InstancedStruct.GetMutable<FGameFeedbackEffectBase>().Play();
	}

	SetState(EGameFeedbackState::Running);
}

void UGameFeedback::PauseFeedback()
{
	if (!ValidateGameFeedbackEffects())
	{
		return;
	}

	for (auto InstancedStruct : GameFeedbackEffects)
	{
		if (!ValidateGameFeedbackEffect(InstancedStruct))
			continue;

		InstancedStruct.GetMutable<FGameFeedbackEffectBase>().Pause();
	}

	SetState(EGameFeedbackState::Paused);
}

void UGameFeedback::ResumeFeedback()
{
	if (!ValidateGameFeedbackEffects())
	{
		return;
	}

	for (auto InstancedStruct : GameFeedbackEffects)
	{
		if (!ValidateGameFeedbackEffect(InstancedStruct))
			continue;

		InstancedStruct.GetMutable<FGameFeedbackEffectBase>().Resume();
	}

	SetState(EGameFeedbackState::Running);
}

void UGameFeedback::StopFeedback()
{
	if (!ValidateGameFeedbackEffects())
	{
		return;
	}

	for (auto InstancedStruct : GameFeedbackEffects)
	{
		if (!ValidateGameFeedbackEffect(InstancedStruct))
			continue;

		InstancedStruct.GetMutable<FGameFeedbackEffectBase>().Stop();
	}

	if (State == EGameFeedbackState::Running || State == EGameFeedbackState::Paused)
	{
		OnGameFeedbackStopped.Broadcast(true);
	}

	ElapsedTime = 0.0f;
	SetState(EGameFeedbackState::Idle);
}

void UGameFeedback::TickFeedback(float DeltaTime)
{
	if (!ValidateGameFeedbackEffects())
	{
		return;
	}

	if (State != EGameFeedbackState::Running)
	{
		return;
	}

	ElapsedTime += DeltaTime;

	bool bAllIdle = true;
	for (auto InstancedStruct : GameFeedbackEffects)
	{
		if (!ValidateGameFeedbackEffect(InstancedStruct))
			continue;

		bAllIdle &= !InstancedStruct.GetMutable<FGameFeedbackEffectBase>().Tick(DeltaTime);
	}

	if (bAllIdle)
	{
		ElapsedTime = 0.0f;
		SetState(EGameFeedbackState::Idle);
	}
}
