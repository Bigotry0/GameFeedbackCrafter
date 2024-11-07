﻿// Copyright (c) Lim Young

#include "GameFeedbackEffectBase.h"

#include "GameFeedback.h"

float UGameFeedbackEffectBase::GetEffectProgress() const
{
	return BasicConfig.GetProgress();
}

//////////////// Context /////////////
#pragma region Context
UWorld* UGameFeedbackEffectBase::TryGetContextWorld() const
{
	if (ContextObject)
	{
		return ContextObject->GetWorld();
	}

	return GetWorld();
}

UGameFeedback* UGameFeedbackEffectBase::GetOwnerFeedback() const
{
	if (UObject* Outer = GetOuter())
	{
		if (UGameFeedback* OwnerFeedback = Cast<UGameFeedback>(Outer))
		{
			return OwnerFeedback;
		}
	}

	return nullptr;
}

EGameFeedbackEffectContextType UGameFeedbackEffectBase::GetContextType() const
{
	return ContextType;
}

UObject* UGameFeedbackEffectBase::GetContextObject() const
{
	return ContextObject;
}

AActor* UGameFeedbackEffectBase::GetContextActor() const
{
	switch (ContextType)
	{
	case EGameFeedbackEffectContextType::Actor:
		return Cast<AActor>(ContextObject);
	case EGameFeedbackEffectContextType::Component:
		return Cast<UActorComponent>(ContextObject)->GetOwner();
	default:
		break;
	}

	return nullptr;
}

bool UGameFeedbackEffectBase::IsOnlyComponentContext() const
{
	return ContextType == EGameFeedbackEffectContextType::Component;
}

bool UGameFeedbackEffectBase::IsOnlyActorContext() const
{
	return ContextType == EGameFeedbackEffectContextType::Actor;
}

bool UGameFeedbackEffectBase::IsOnlyWorldContext() const
{
	return ContextType == EGameFeedbackEffectContextType::World;
}

bool UGameFeedbackEffectBase::IsOnlyStaticContext() const
{
	return ContextType == EGameFeedbackEffectContextType::Static;
}

bool UGameFeedbackEffectBase::IsOnlyActorOrComponentContext() const
{
	return ContextType == EGameFeedbackEffectContextType::Actor || ContextType ==
		EGameFeedbackEffectContextType::Component;
}

bool UGameFeedbackEffectBase::IsExcludeStaticContext() const
{
	return ContextType != EGameFeedbackEffectContextType::Static;
}
#pragma endregion
//////////////// Life cycle /////////////
#pragma region LifeCycle
void UGameFeedbackEffectBase::Init(UGameFeedback* InGameFeedback, const EGameFeedbackEffectContextType InContextType,
                                   UObject* InContextObject)
{
	OwnerGameFeedback = InGameFeedback;
	ContextType = InContextType;
	ContextObject = InContextObject;

	if (UWorld* World = TryGetContextWorld())
	{
		ContextWorldSettings = World->GetWorldSettings();
	}

	BasicConfig.Timing.Reset();
	BasicConfig.SetShouldPlayAfterCooldown(false);

	OnInit();

	BasicConfig.State = EGameFeedbackEffectState::Idle;
}

void UGameFeedbackEffectBase::Play()
{
	switch (BasicConfig.State)
	{
	case EGameFeedbackEffectState::Cooldown:
		BasicConfig.SetShouldPlayAfterCooldown(true);
		break;
	case EGameFeedbackEffectState::Idle:
		if (BasicConfig.Timing.IsUseDelay())
		{
			BasicConfig.State = EGameFeedbackEffectState::Delay;
		}
		else
		{
			OnPlay();

			BasicConfig.State = EGameFeedbackEffectState::Running;
		}
		break;
	default:
		break;
	}
}

void UGameFeedbackEffectBase::Pause()
{
	switch (BasicConfig.State)
	{
	case EGameFeedbackEffectState::Running:
		OnPause();
	case EGameFeedbackEffectState::Delay:
	case EGameFeedbackEffectState::Cooldown:
		BasicConfig.State = EGameFeedbackEffectState::Paused;
	default:
		break;
	}
}

void UGameFeedbackEffectBase::Resume()
{
	switch (BasicConfig.State)
	{
	case EGameFeedbackEffectState::Paused:
		if (BasicConfig.Timing.IsOnCoolDown())
		{
			BasicConfig.State = EGameFeedbackEffectState::Cooldown;
			return;
		}

		if (BasicConfig.Timing.IsOnDelay())
		{
			BasicConfig.State = EGameFeedbackEffectState::Delay;
			return;
		}

		OnResume();
		BasicConfig.State = EGameFeedbackEffectState::Running;
		break;
	default:
		break;
	}
}

void UGameFeedbackEffectBase::Stop(bool& bOnCooldown)
{
	bOnCooldown = false;

	switch (BasicConfig.State)
	{
	case EGameFeedbackEffectState::Running:
	case EGameFeedbackEffectState::Paused:
		OnStop(true);

		if (BasicConfig.Timing.IsUseCoolDown())
		{
			BasicConfig.Timing.ResetAtEnd();
			BasicConfig.State = EGameFeedbackEffectState::Cooldown;
			bOnCooldown = true;
			break;
		}

		BasicConfig.Timing.Reset();
		BasicConfig.State = EGameFeedbackEffectState::Idle;
		break;
	case EGameFeedbackEffectState::Delay:
		BasicConfig.Timing.Reset();
		BasicConfig.State = EGameFeedbackEffectState::Idle;
		break;
	case EGameFeedbackEffectState::Cooldown:
		bOnCooldown = true;
		break;
	default:
		break;
	}
}

bool UGameFeedbackEffectBase::Tick(float DeltaTime)
{
	switch (BasicConfig.State)
	{
	case EGameFeedbackEffectState::Running:
		OnTick(DeltaTime);

		if (!BasicConfig.Timing.Tick(DeltaTime, GetContextWorldTimeDilation()))
		{
			OnStop(false);

			if (BasicConfig.Timing.IsUseCoolDown())
			{
				BasicConfig.State = EGameFeedbackEffectState::Cooldown;
			}
			else
			{
				BasicConfig.Timing.Reset();

				BasicConfig.State = EGameFeedbackEffectState::Idle;
			}
		}

		return true;
	case EGameFeedbackEffectState::Delay:
		BasicConfig.Timing.Tick(DeltaTime, GetContextWorldTimeDilation());

		if (!BasicConfig.Timing.IsOnDelay())
		{
			BasicConfig.State = EGameFeedbackEffectState::Running;
		}

		return true;
	case EGameFeedbackEffectState::Cooldown:
		BasicConfig.Timing.Tick(DeltaTime, GetContextWorldTimeDilation());

		if (BasicConfig.Timing.IsCoolDownEnd())
		{
			BasicConfig.Timing.Reset();

			if (BasicConfig.ShouldPlayAfterCooldown())
			{
				if (BasicConfig.Timing.IsUseDelay())
				{
					BasicConfig.State = EGameFeedbackEffectState::Delay;
				}
				else
				{
					OnPlay();

					BasicConfig.State = EGameFeedbackEffectState::Running;
				}

				BasicConfig.SetShouldPlayAfterCooldown(false);
			}
			else
			{
				BasicConfig.State = EGameFeedbackEffectState::Idle;
			}
		}

		return true;
	default:
		break;
	}

	return false;
}

void UGameFeedbackEffectBase::Reset()
{
	if (BasicConfig.State != EGameFeedbackEffectState::NotInitialized)
	{
		BasicConfig.Timing.ResetToZero();

		BasicConfig.State = EGameFeedbackEffectState::NotInitialized;
	}
}

bool UGameFeedbackEffectBase::InIdleOrNotInitializedState() const
{
	return BasicConfig.State == EGameFeedbackEffectState::NotInitialized ||
		BasicConfig.State == EGameFeedbackEffectState::Idle;
}
#pragma endregion

#pragma region Timing
float UGameFeedbackEffectBase::GetContextWorldTimeDilation() const
{
	return ContextWorldSettings ? ContextWorldSettings->TimeDilation : 1.0f;
}
#pragma endregion
