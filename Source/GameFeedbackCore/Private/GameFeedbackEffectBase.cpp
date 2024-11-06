// Copyright (c) Lim Young

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

	OnInit();

	BasicConfig.State = EGameFeedbackEffectState::Idle;
}

void UGameFeedbackEffectBase::Play()
{
	OnPlay();

	if (BasicConfig.Timing.IsUseDelay())
	{
		BasicConfig.State = EGameFeedbackEffectState::Delay;
	}
	else
	{
		BasicConfig.State = EGameFeedbackEffectState::Running;
	}
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

		BasicConfig.Timing.Reset();

		BasicConfig.State = EGameFeedbackEffectState::Idle;
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

			BasicConfig.Timing.Reset();

			BasicConfig.State = EGameFeedbackEffectState::Idle;
		}

		return true;
	case EGameFeedbackEffectState::Delay:
		if (!BasicConfig.Timing.Tick(DeltaTime, GetContextWorldTimeDilation()))
		{
			OnStop(false);

			BasicConfig.Timing.Reset();

			BasicConfig.State = EGameFeedbackEffectState::Idle;
		}

		if (!BasicConfig.Timing.IsOnDelay())
		{
			BasicConfig.State = EGameFeedbackEffectState::Running;
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
		BasicConfig.Timing.Reset();

		BasicConfig.State = EGameFeedbackEffectState::NotInitialized;
	}
}
#pragma endregion

#pragma region Timing
float UGameFeedbackEffectBase::GetContextWorldTimeDilation() const
{
	return ContextWorldSettings ? ContextWorldSettings->TimeDilation : 1.0f;
}
#pragma endregion
