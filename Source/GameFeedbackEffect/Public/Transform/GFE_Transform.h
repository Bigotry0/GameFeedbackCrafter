// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "Common/InterpolatorGameFeedbackEffectBase.h"
#include "GFE_Transform.generated.h"

UENUM(BlueprintType)
enum class ETransformSpace : uint8
{
	World,
	Local
};

/**
 * Base class for transform effects.
 */
UCLASS(Abstract)
class GAMEFEEDBACKEFFECT_API UGFE_TransformBase : public UInterpolatorGameFeedbackEffectBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Transform", meta = (DisplayPriority = 0))
	FGFActorSelection ActorSelection;

	UPROPERTY(EditAnywhere, Category = "Transform", meta = (DisplayPriority = 1))
	ETransformSpace TransformSpace = ETransformSpace::Local;

	bool bValid = false;
	bool bUseCustomTargetComponent = false;

	virtual void OnInit() override;

#if WITH_EDITOR
	virtual EGameFeedbackEffectType GetEffectType() const override
	{
		return EGameFeedbackEffectType::Transform;
	}
#endif
};

#pragma region Transform_Location
UCLASS()
class UGFE_Transform_Location : public UGFE_TransformBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Transform|Location")
	FVector StartLocation;

	UPROPERTY(EditAnywhere, Category = "Transform|Location")
	FVector EndLocation;

	virtual void OnPlay() override;
	virtual void OnStop(bool bInterrupted) override;
	virtual void OnTick(float DeltaTime) override;

private:
	void SetTargetLocation(const FVector& NewLocation);
};
#pragma endregion

#pragma region Transform_Rotation
UENUM(BlueprintType)
enum class ERotateMode : uint8
{
	Absolute,
	Additive,
	ToTarget
};

UENUM(BlueprintType)
enum class ERotateLerpMode : uint8
{
	FastLerp,
	Slerp
};

UCLASS()
class UGFE_Transform_Rotation : public UGFE_TransformBase
{
	GENERATED_BODY()

private:
	FQuat StartQuat;
	FQuat EndQuat;

	FVector StartEuler;
	FVector EndEuler;

protected:
	UPROPERTY(EditAnywhere, Category = "Transform|Rotation")
	ERotateMode RotateMode = ERotateMode::Absolute;

	UPROPERTY(EditAnywhere, Category = "Transform|Rotation")
	FRotator StartRotation;

	UPROPERTY(EditAnywhere, Category = "Transform|Rotation")
	FRotator EndRotation;

	UPROPERTY(EditAnywhere, Category = "Transform|Rotation")
	bool bUseQuatLerp = false;

	UPROPERTY(EditAnywhere, Category = "Transform|Rotation",
		meta = (EditCondition = "bUseQuatLerp", EditConditionHides = true))
	ERotateLerpMode RotateLerpMode = ERotateLerpMode::FastLerp;

	virtual void OnPlay() override;
	virtual void OnStop(bool bInterrupted) override;
	virtual void OnTick(float DeltaTime) override;

private:
	void QuatLerp(float Alpha, FQuat& NewQuat) const;
	void SetTargetRotation(const FRotator& NewRotation);
};
#pragma endregion

#pragma region Transform_Scale
UCLASS()
class UGFE_Transform_Scale : public UGFE_TransformBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Transform|Scale")
	FVector StartScale = FVector(1.0f);

	UPROPERTY(EditAnywhere, Category = "Transform|Scale")
	FVector EndScale = FVector(1.0f);

	virtual void OnPlay() override;
	virtual void OnStop(bool bInterrupted) override;
	virtual void OnTick(float DeltaTime) override;

private:
	void SetTargetScale(const FVector& NewScale);
};
#pragma endregion
