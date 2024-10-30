// Copyright (c) Lim Young


#include "Transform/GFE_Transform.h"

void UGFE_TransformBase::OnInit()
{
	Super::OnInit();

	ActorSelection.Init(GetContextType(), GetContextActor());

	if (ActorSelection.IsUseCustomTargetComponent())
	{
		bValid = ActorSelection.IsComponentValid();
		if (bValid)
		{
			bUseCustomTargetComponent = true;
		}
	}
	else
	{
		bValid = ActorSelection.IsActorValid();
		bUseCustomTargetComponent = false;
	}
}

/// Location
void UGFE_Transform_Location::OnPlay()
{
	Super::OnPlay();

	if (!bValid)
	{
		return;
	}

	SetTargetLocation(StartLocation);
}

void UGFE_Transform_Location::OnStop(bool bInterrupted)
{
	Super::OnStop(bInterrupted);

	if (!bValid)
	{
		return;
	}

	SetTargetLocation(EndLocation);
}

void UGFE_Transform_Location::OnTick(float DeltaTime)
{
	Super::OnTick(DeltaTime);

	if (!bValid)
	{
		return;
	}

	const float Alpha = GetInterpolatorAlpha();
	const FVector NewLocation = FMath::Lerp(StartLocation, EndLocation, Alpha);

	SetTargetLocation(NewLocation);
}

void UGFE_Transform_Location::SetTargetLocation(FVector NewLocation)
{
	switch (TransformSpace)
	{
	case ETransformSpace::World:
		if (bUseCustomTargetComponent)
		{
			USceneComponent* TargetComponent = Cast<USceneComponent>(ActorSelection.GetTargetComponent());
			if (TargetComponent)
			{
				TargetComponent->SetWorldLocation(NewLocation);
			}
		}
		else
		{
			ActorSelection.GetTargetActor()->SetActorLocation(NewLocation);
		}
		break;
	case ETransformSpace::Local:
		if (bUseCustomTargetComponent)
		{
			USceneComponent* TargetComponent = Cast<USceneComponent>(ActorSelection.GetTargetComponent());
			if (TargetComponent)
			{
				TargetComponent->SetRelativeLocation(NewLocation);
			}
		}
		else
		{
			ActorSelection.GetTargetActor()->SetActorRelativeLocation(NewLocation);
		}
		break;
	default:
		break;
	}
}
