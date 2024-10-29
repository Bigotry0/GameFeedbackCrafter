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

	virtual void OnInit() override;
};

UCLASS()
class UGFE_Transform_Location : public UGFE_TransformBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Transform|Location")
	bool bValid = false;
	UPROPERTY(EditAnywhere, Category = "Transform|Location")
	bool bUseCustomTargetComponent = false;

protected:
	UPROPERTY(EditAnywhere, Category = "Transform|Location")
	FVector StartLocation;

	UPROPERTY(EditAnywhere, Category = "Transform|Location")
	FVector EndLocation;

	virtual void OnPlay() override;
	virtual void OnInit() override;
	virtual void OnStop(bool bInterrupted) override;
	virtual void OnTick(float DeltaTime) override;
};
