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

void UGFE_TransformBase::OnPlay()
{
	Super::OnPlay();

	if (bUseNoise)
	{
		Noise.UpdateNoise();
	}
}

#pragma region Transform_Location
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

	SetTargetLocation(FMath::Lerp(StartLocation, EndLocation, GetInterpolatorAlpha()));
}

void UGFE_Transform_Location::OnTick(float DeltaTime)
{
	Super::OnTick(DeltaTime);

	if (!bValid)
	{
		return;
	}

	SetTargetLocation(FMath::Lerp(StartLocation, EndLocation, GetInterpolatorAlpha()));
}

void UGFE_Transform_Location::SetTargetLocation(const FVector& NewLocation)
{
	switch (TransformSpace)
	{
	case ETransformSpace::World:
		if (bUseCustomTargetComponent)
		{
			USceneComponent* TargetComponent = Cast<USceneComponent>(ActorSelection.GetTargetComponent());
			if (TargetComponent)
			{
				TargetComponent->SetWorldLocation(NewLocation + (bUseNoise
					                                                 ? Noise.GetNoise3D(GetEffectProgress())
					                                                 : FVector::ZeroVector));
			}
		}
		else
		{
			ActorSelection.GetTargetActor()->SetActorLocation(NewLocation + (bUseNoise
				                                                                 ? Noise.GetNoise3D(GetEffectProgress())
				                                                                 : FVector::ZeroVector));
		}
		break;
	case ETransformSpace::Local:
		if (bUseCustomTargetComponent)
		{
			USceneComponent* TargetComponent = Cast<USceneComponent>(ActorSelection.GetTargetComponent());
			if (TargetComponent)
			{
				TargetComponent->SetRelativeLocation(NewLocation + (bUseNoise
					                                                    ? Noise.GetNoise3D(GetEffectProgress())
					                                                    : FVector::ZeroVector));
			}
		}
		else
		{
			ActorSelection.GetTargetActor()->SetActorRelativeLocation(NewLocation + (bUseNoise
					? Noise.GetNoise3D(GetEffectProgress())
					: FVector::ZeroVector));
		}
		break;
	default:
		break;
	}
}
#pragma endregion

#pragma region Transform_Rotation
void UGFE_Transform_Rotation::OnPlay()
{
	Super::OnPlay();

	if (!bValid)
	{
		return;
	}

	if (bUseQuatLerp)
	{
		StartQuat = StartRotation.Quaternion();
		EndQuat = EndRotation.Quaternion();
	}
	else
	{
		StartEuler = StartRotation.Euler();
		EndEuler = EndRotation.Euler();
	}

	SetTargetRotation(StartRotation);
}

void UGFE_Transform_Rotation::OnStop(bool bInterrupted)
{
	Super::OnStop(bInterrupted);

	if (!bValid)
	{
		return;
	}

	if (bUseQuatLerp)
	{
		FQuat NewQuat;
		QuatLerp(GetInterpolatorAlpha(), NewQuat);

		SetTargetRotation(NewQuat.Rotator());
	}
	else
	{
		const FVector NewEuler = FMath::Lerp(StartEuler, EndEuler, GetInterpolatorAlpha());
		SetTargetRotation(FRotator(NewEuler.Y, NewEuler.Z, NewEuler.X));
	}
}

void UGFE_Transform_Rotation::OnTick(float DeltaTime)
{
	Super::OnTick(DeltaTime);

	if (!bValid)
	{
		return;
	}

	if (bUseQuatLerp)
	{
		FQuat NewQuat;
		QuatLerp(GetInterpolatorAlpha(), NewQuat);

		SetTargetRotation(NewQuat.Rotator());
	}
	else
	{
		const FVector NewEuler = FMath::Lerp(StartEuler, EndEuler, GetInterpolatorAlpha());
		SetTargetRotation(FRotator(NewEuler.Y, NewEuler.Z, NewEuler.X));
	}
}

void UGFE_Transform_Rotation::QuatLerp(const float Alpha, FQuat& NewQuat) const
{
	switch (RotateLerpMode)
	{
	case ERotateLerpMode::FastLerp:
		NewQuat = FQuat::FastLerp(StartQuat, EndQuat, Alpha);
		break;
	case ERotateLerpMode::Slerp:
		NewQuat = FQuat::Slerp(StartQuat, EndQuat, Alpha);
		break;
	default:
		break;
	}
}

void UGFE_Transform_Rotation::SetTargetRotation(const FRotator& NewRotation)
{
	switch (TransformSpace)
	{
	case ETransformSpace::World:
		if (bUseCustomTargetComponent)
		{
			USceneComponent* TargetComponent = Cast<USceneComponent>(ActorSelection.GetTargetComponent());
			if (TargetComponent)
			{
				TargetComponent->SetWorldRotation(NewRotation + (bUseNoise
					                                                 ? Noise.GetNoise3D(GetEffectProgress()).Rotation()
					                                                 : FRotator::ZeroRotator));
			}
		}
		else
		{
			ActorSelection.GetTargetActor()->SetActorRotation(NewRotation + (bUseNoise
				                                                                 ? Noise.GetNoise3D(GetEffectProgress())
				                                                                 .Rotation()
				                                                                 : FRotator::ZeroRotator));
		}
		break;
	case ETransformSpace::Local:
		if (bUseCustomTargetComponent)
		{
			USceneComponent* TargetComponent = Cast<USceneComponent>(ActorSelection.GetTargetComponent());
			if (TargetComponent)
			{
				TargetComponent->SetRelativeRotation(NewRotation + (bUseNoise
					                                                    ? Noise.GetNoise3D(GetEffectProgress()).
					                                                    Rotation()
					                                                    : FRotator::ZeroRotator));
			}
		}
		else
		{
			ActorSelection.GetTargetActor()->SetActorRelativeRotation(NewRotation + (bUseNoise
					? Noise.GetNoise3D(GetEffectProgress()).Rotation()
					: FRotator::ZeroRotator));
		}
		break;
	default:
		break;
	}
}
#pragma endregion

#pragma region Transform_Scale
void UGFE_Transform_Scale::OnPlay()
{
	Super::OnPlay();

	if (!bValid)
	{
		return;
	}

	SetTargetScale(StartScale);
}

void UGFE_Transform_Scale::OnStop(bool bInterrupted)
{
	Super::OnStop(bInterrupted);

	if (!bValid)
	{
		return;
	}

	SetTargetScale(FMath::Lerp(StartScale, EndScale, GetInterpolatorAlpha()));
}

void UGFE_Transform_Scale::OnTick(float DeltaTime)
{
	Super::OnTick(DeltaTime);

	if (!bValid)
	{
		return;
	}

	SetTargetScale(FMath::Lerp(StartScale, EndScale, GetInterpolatorAlpha()));
}

void UGFE_Transform_Scale::SetTargetScale(const FVector& NewScale)
{
	switch (TransformSpace)
	{
	case ETransformSpace::World:
		if (bUseCustomTargetComponent)
		{
			USceneComponent* TargetComponent = Cast<USceneComponent>(ActorSelection.GetTargetComponent());
			if (TargetComponent)
			{
				TargetComponent->SetWorldScale3D(NewScale + (bUseNoise
					                                             ? Noise.GetNoise3D(GetEffectProgress())
					                                             : FVector::ZeroVector));
			}
		}
		else
		{
			ActorSelection.GetTargetActor()->SetActorScale3D(NewScale + (bUseNoise
				                                                             ? Noise.GetNoise3D(GetEffectProgress())
				                                                             : FVector::ZeroVector));
		}
		break;
	case ETransformSpace::Local:
		if (bUseCustomTargetComponent)
		{
			USceneComponent* TargetComponent = Cast<USceneComponent>(ActorSelection.GetTargetComponent());
			if (TargetComponent)
			{
				TargetComponent->SetRelativeScale3D(NewScale + (bUseNoise
					                                                ? Noise.GetNoise3D(GetEffectProgress())
					                                                : FVector::ZeroVector));
			}
		}
		else
		{
			ActorSelection.GetTargetActor()->SetActorRelativeScale3D(NewScale + (bUseNoise
					? Noise.GetNoise3D(GetEffectProgress())
					: FVector::ZeroVector));
		}
		break;
	default:
		break;
	}
}

#pragma endregion
