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

bool UGameFeedback::ValidateGameFeedbackEffect(const UGameFeedbackEffectBase* GameFeedbackEffect)
{
	if (!GameFeedbackEffect)
	{
#if WITH_EDITOR
		UE_LOG(GameFeedbackCoreLog, Warning, TEXT("GameFeedbackEffect is nullptr."));
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

void UGameFeedback::InitFeedback(const EGameFeedbackEffectContextType InContextType, UObject* InContextObject)
{
	if (!ValidateGameFeedbackEffects())
	{
		return;
	}

	if (State == EGameFeedbackState::NotInitialized)
	{
		ElapsedTime = 0.0f;

		for (const auto GFE : GameFeedbackEffects)
		{
			if (!ValidateGameFeedbackEffect(GFE))
				continue;

			GFE->Init(this, InContextType, InContextObject);
		}

		SetState(EGameFeedbackState::Idle);
	}
}

void UGameFeedback::PlayFeedback(const EGameFeedbackPlayDirection InPlayDirection)
{
	if (!ValidateGameFeedbackEffects())
	{
		return;
	}

	if (State == EGameFeedbackState::Idle || State == EGameFeedbackState::Running)
	{
		PlayDirection = InPlayDirection;
		
		for (const auto GFE : GameFeedbackEffects)
		{
			if (!ValidateGameFeedbackEffect(GFE))
				continue;

			GFE->Play();
		}

		SetState(EGameFeedbackState::Running);
	}
}

void UGameFeedback::PauseFeedback()
{
	if (!ValidateGameFeedbackEffects())
	{
		return;
	}

	if (State == EGameFeedbackState::Running)
	{
		for (const auto GFE : GameFeedbackEffects)
		{
			if (!ValidateGameFeedbackEffect(GFE))
				continue;

			GFE->Pause();
		}

		SetState(EGameFeedbackState::Paused);
	}
}

void UGameFeedback::ResumeFeedback()
{
	if (!ValidateGameFeedbackEffects())
	{
		return;
	}

	if (State == EGameFeedbackState::Paused)
	{
		for (const auto GFE : GameFeedbackEffects)
		{
			if (!ValidateGameFeedbackEffect(GFE))
				continue;

			GFE->Resume();
		}

		SetState(EGameFeedbackState::Running);
	}
}

void UGameFeedback::StopFeedback()
{
	if (!ValidateGameFeedbackEffects())
	{
		return;
	}

	if (State == EGameFeedbackState::Running || State == EGameFeedbackState::Paused)
	{
		bool bAnyOnCooldown = false;

		bool bGFEOnCooldown;
		for (const auto GFE : GameFeedbackEffects)
		{
			if (!ValidateGameFeedbackEffect(GFE))
				continue;

			GFE->Stop(bGFEOnCooldown);
			bAnyOnCooldown |= bGFEOnCooldown;
		}

		OnGameFeedbackStopped.Broadcast(true);

		if (!bAnyOnCooldown)
		{
			ElapsedTime = 0.0f;
			SetState(EGameFeedbackState::Idle);
		}
	}
}

void UGameFeedback::TickFeedback(float DeltaTime)
{
	if (!ValidateGameFeedbackEffects())
	{
		return;
	}

	if (State == EGameFeedbackState::Running)
	{
		ElapsedTime += DeltaTime;

		bool bAllIdle = true;
		for (const auto GFE : GameFeedbackEffects)
		{
			if (!ValidateGameFeedbackEffect(GFE))
				continue;

			bAllIdle &= !GFE->Tick(DeltaTime);
		}

		if (bAllIdle)
		{
			ElapsedTime = 0.0f;
			SetState(EGameFeedbackState::Idle);
		}
	}
}

void UGameFeedback::ResetFeedback()
{
	if (!ValidateGameFeedbackEffects())
	{
		return;
	}

	if (State != EGameFeedbackState::NotInitialized)
	{
		for (const auto GFE : GameFeedbackEffects)
		{
			if (!ValidateGameFeedbackEffect(GFE))
				continue;

			GFE->Reset();
		}

		ElapsedTime = 0.0f;
		SetState(EGameFeedbackState::NotInitialized);
	}
}
