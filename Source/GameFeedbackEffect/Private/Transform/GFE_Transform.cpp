// Copyright (c) Lim Young


#include "Transform/GFE_Transform.h"

void UGFE_TransformBase::OnInit()
{
	Super::OnInit();

	ActorSelection.Init(GetContextType(), GetContextActor());
}

void UGFE_Transform_Location::OnPlay()
{
	Super::OnPlay();

	if (!bValid)
	{
		return;
	}

	switch (TransformSpace)
	{
	case ETransformSpace::World:
		if (bUseCustomTargetComponent)
		{
			//TODO : Implement
		}
		else
		{
			ActorSelection.GetTargetActor()->SetActorLocation(StartLocation);
		}
		break;
	case ETransformSpace::Local:
		if (bUseCustomTargetComponent)
		{
			//TODO : Implement
		}
		else
		{
			ActorSelection.GetTargetActor()->SetActorRelativeLocation(StartLocation);
		}
	default:
		break;
	}
}

void UGFE_Transform_Location::OnInit()
{
	Super::OnInit();

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

void UGFE_Transform_Location::OnStop(bool bInterrupted)
{
	Super::OnStop(bInterrupted);

	if (!bValid)
	{
		return;
	}

	switch (TransformSpace)
	{
	case ETransformSpace::World:
		if (bUseCustomTargetComponent)
		{
			//TODO : Implement
		}
		else
		{
			ActorSelection.GetTargetActor()->SetActorLocation(EndLocation);
		}
		break;
	case ETransformSpace::Local:
		if (bUseCustomTargetComponent)
		{
			//TODO : Implement
		}
		else
		{
			ActorSelection.GetTargetActor()->SetActorRelativeLocation(EndLocation);
		}
		break;
	default:
		break;
	}
}

void UGFE_Transform_Location::OnTick(float DeltaTime)
{
	Super::OnTick(DeltaTime);

	if (!bValid)
	{
		return;
	}

	float Alpha = GetInterpolatorAlpha();
	FVector NewLocation = FMath::Lerp(StartLocation, EndLocation, Alpha);

	switch (TransformSpace)
	{
	case ETransformSpace::World:
		if (bUseCustomTargetComponent)
		{
			//TODO : Implement
		}
		else
		{
			ActorSelection.GetTargetActor()->SetActorLocation(NewLocation);
		}
		break;
	case ETransformSpace::Local:
		if (bUseCustomTargetComponent)
		{
			//TODO : Implement
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
