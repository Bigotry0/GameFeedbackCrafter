// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "Common/GFE_InterpolatorGameFeedbackEffectBase.h"
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
class GAMEFEEDBACKEFFECT_API UGFE_TransformBase : public UGFE_InterpolatorGameFeedbackEffectBase
{
	GENERATED_BODY()

protected:
	/**
	 * Actor selection, used to determine the target actor/component.
	 * You can specify the target actor/component directly or use the self actor/component.
	 * Self actor/component is the context actor/component of the effect.
	 */
	UPROPERTY(EditAnywhere, Category = "Transform", meta = (DisplayPriority = 0))
	FGFActorSelection ActorSelection;

	/**
	 * Transform space for the target actor/component. (World or Local)
	 */
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
/**
 * Transforms the location of the target actor/component.
 */
UCLASS()
class UGFE_Transform_Location : public UGFE_TransformBase
{
	GENERATED_BODY()

protected:
	/**
	 * Start location of the target actor/component.
	 */
	UPROPERTY(EditAnywhere, Category = "Transform|Location")
	FVector StartLocation;

	/**
	 * End location of the target actor/component.
	 */
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
/**
 * Rotation mode for the target actor/component.
 */
UENUM(BlueprintType)
enum class ERotateMode : uint8
{
	Absolute,
	Additive,
	ToTarget
};

/**
 * Lerp mode for quaternion lerp.
 */
UENUM(BlueprintType)
enum class ERotateLerpMode : uint8
{
	FastLerp,
	Slerp
};

/**
 * Transforms the rotation of the target actor/component.
 */
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
	/**
	 * Rotation mode for the target actor/component 
	 * Absolute: Set the rotation directly 
	 * Additive: Add the rotation to the current rotation 
	 * ToTarget: Rotate to the target rotation
	 */
	UPROPERTY(EditAnywhere, Category = "Transform|Rotation")
	ERotateMode RotateMode = ERotateMode::Absolute;

	/**
	 * Start rotation of the target actor/component.
	 */
	UPROPERTY(EditAnywhere, Category = "Transform|Rotation")
	FRotator StartRotation;

	/**
	 * End rotation of the target actor/component.
	 */
	UPROPERTY(EditAnywhere, Category = "Transform|Rotation")
	FRotator EndRotation;

	/**
	 * Use quaternion lerp instead of euler lerp.
	 */
	UPROPERTY(EditAnywhere, Category = "Transform|Rotation")
	bool bUseQuatLerp = false;

	/**
	 * Lerp mode for quaternion lerp.
	 */
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
/**
 * Transforms the scale of the target actor/component.
 */
UCLASS()
class UGFE_Transform_Scale : public UGFE_TransformBase
{
	GENERATED_BODY()

protected:
	/**
	 * Start scale of the target actor/component.
	 */
	UPROPERTY(EditAnywhere, Category = "Transform|Scale")
	FVector StartScale = FVector(1.0f);

	/**
	 * End scale of the target actor/component.
	 */
	UPROPERTY(EditAnywhere, Category = "Transform|Scale")
	FVector EndScale = FVector(1.0f);

	virtual void OnPlay() override;
	virtual void OnStop(bool bInterrupted) override;
	virtual void OnTick(float DeltaTime) override;

private:
	void SetTargetScale(const FVector& NewScale);
};
#pragma endregion
