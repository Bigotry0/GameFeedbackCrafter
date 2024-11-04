// Copyright (c) Lim Young

#include "GameFeedbackEffectBase.h"

#include "GameFeedback.h"

float UGameFeedbackEffectBase::GetEffectProgress() const
{
	return BasicConfig.GetProgress();
}

//////////////// Context /////////////

UWorld* UGameFeedbackEffectBase::TryGetContextWorld() const
{
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

//////////////// Life cycle /////////////

void UGameFeedbackEffectBase::Init(UGameFeedback* InGameFeedback, const EGameFeedbackEffectContextType InContextType,
                                   UObject* InContextObject)
{
	OwnerGameFeedback = InGameFeedback;
	ContextType = InContextType;
	ContextObject = InContextObject;

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

void UGameFeedbackEffectBase::Reset()
{
	if (BasicConfig.State != EGameFeedbackEffectState::NotInitialized)
	{
		BasicConfig.ElapsedTime = 0.0f;

		BasicConfig.State = EGameFeedbackEffectState::NotInitialized;
	}
}
