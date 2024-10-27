// Copyright (c) Lim Young

#include "GameFeedbackEffectBase.h"

#include "GameFeedback.h"

UGameFeedbackEffectBase::UGameFeedbackEffectBase()
{
	UGameFeedback* OwnerFeedback = GetOwnerFeedback();
	if (OwnerFeedback)
	{
		UObject* Outer = OwnerFeedback->GetOuter();
		if (!Outer)
		{
			ContextType = EGameFeedbackEffectContextType::Static;
		}
		else if (AActor* ContextActor = Cast<AActor>(Outer))
		{
			ContextType = EGameFeedbackEffectContextType::Actor;
		}
		else if (UActorComponent* ContextComponent = Cast<UActorComponent>(Outer))
		{
			ContextType = EGameFeedbackEffectContextType::Component;
		}
		else
		{
			if (UWorld* ContextWorld = TryGetContextWorld())
			{
				ContextType = EGameFeedbackEffectContextType::World;
			}
			else
			{
				ContextType = EGameFeedbackEffectContextType::Static;
			}
		}
	}

#if WITH_EDITOR
	EffectTypeColor = GetTypeColor(GetEffectTypeFromChildClass());
#endif
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

UWorld* UGameFeedbackEffectBase::TryGetContextWorld() const
{
	return GetWorld();
}

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
