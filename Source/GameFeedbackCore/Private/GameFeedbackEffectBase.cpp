// Copyright (c) Lim Young

#include "GameFeedbackEffectBase.h"

#include "GameFeedback.h"

#pragma region GameFeedbackEffectTiming

#pragma region LifeCycle
bool FGameFeedbackEffectTiming::Tick(float DeltaTime, float TimeDilation)
{
	if (Duration == 0.0f)
	{
		return false;
	}

	const float DeltaTimeScaled = TimeScaleMode == ETimeScaleMode::Scaled ? DeltaTime * TimeDilation : DeltaTime;
	ElapsedTime += DeltaTimeScaled;

	return !(ElapsedTime >= Duration);
}

float FGameFeedbackEffectTiming::GetProgress() const
{
	if (Duration == 0.0f)
	{
		if (PlayDirection == Backward)
		{
			return 0.0f;
		}

		return 1.0f;
	}

	float Progress = FMath::Clamp(ElapsedTime / Duration, 0.0f, 1.0f);

	if (PlayDirection == Backward)
	{
		Progress = 1.0f - Progress;
	}

	return Progress;
}
#pragma endregion

#pragma region Reset
void FGameFeedbackEffectTiming::Reset()
{
	if (Delay > 0.0f)
	{
		ElapsedTime = -Delay;
	}
	else
	{
		ElapsedTime = 0.0f;
	}
}

void FGameFeedbackEffectTiming::ResetToZero()
{
	ElapsedTime = 0.0f;
}

void FGameFeedbackEffectTiming::ResetAtEnd()
{
	ElapsedTime = Duration;
}
#pragma endregion

#pragma region Delay
bool FGameFeedbackEffectTiming::IsUseDelay() const
{
	return Delay > 0.0f;
}

bool FGameFeedbackEffectTiming::IsOnDelay() const
{
	return ElapsedTime < 0.0f;
}
#pragma endregion

#pragma region CoolDown
bool FGameFeedbackEffectTiming::IsUseCoolDown() const
{
	return CoolDown > 0.0f;
}

bool FGameFeedbackEffectTiming::IsOnCoolDown() const
{
	return IsUseCoolDown() && ElapsedTime >= Duration;
}

bool FGameFeedbackEffectTiming::IsCoolDownEnd() const
{
	return ElapsedTime >= Duration + CoolDown;
}
#pragma endregion

#pragma region Repeat
bool FGameFeedbackEffectTiming::IsUseRepeat() const
{
	return bRepeatForever || NumOfRepeats > 0;
}

bool FGameFeedbackEffectTiming::Repeat()
{
	if (bRepeatForever)
	{
		ElapsedTime = -DelayBetweenRepeats;
		return true;
	}

	if (NumOfRepeats < 0)
	{
		return false;
	}

	if (RepeatCount >= NumOfRepeats)
	{
		RepeatCount = 0;
		return false;
	}

	ElapsedTime = -DelayBetweenRepeats;
	RepeatCount++;

	return true;
}
#pragma endregion

#pragma region PlayDirection
void FGameFeedbackEffectTiming::UpdatePlayDirection(EGameFeedbackPlayDirection FeedbackPlayDirection)
{
	switch (EffectPlayDirection)
	{
	case EGameFeedbackEffectPlayDirection::FollowFeedback:
		if (FeedbackPlayDirection == EGameFeedbackPlayDirection::Forward)
		{
			PlayDirection = Forward;
		}
		else
		{
			PlayDirection = Backward;
		}
		break;
	case EGameFeedbackEffectPlayDirection::OppositeFeedback:
		if (FeedbackPlayDirection == EGameFeedbackPlayDirection::Forward)
		{
			PlayDirection = Backward;
		}
		else
		{
			PlayDirection = Forward;
		}
		break;
	case EGameFeedbackEffectPlayDirection::AlwaysForward:
		PlayDirection = Forward;
		break;
	case EGameFeedbackEffectPlayDirection::AlwaysBackward:
		PlayDirection = Backward;
		break;
	}
}
#pragma endregion

#pragma endregion

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
	BasicConfig.Timing.UpdatePlayDirection(OwnerGameFeedback->GetPlayDirection());
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
			PlayEffect();
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

			if (BasicConfig.Timing.IsUseRepeat() && BasicConfig.Timing.Repeat())
			{
				if (BasicConfig.Timing.IsOnDelay())
				{
					BasicConfig.State = EGameFeedbackEffectState::Delay;
				}
				else
				{
					PlayEffect();
				}

				return true;
			}

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
			PlayEffect();
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
					PlayEffect();
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

void UGameFeedbackEffectBase::PlayEffect()
{
	BasicConfig.Timing.UpdatePlayDirection(OwnerGameFeedback->GetPlayDirection());

	OnPlay();

	BasicConfig.State = EGameFeedbackEffectState::Running;
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
