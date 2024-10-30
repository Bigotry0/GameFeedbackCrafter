// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "GameFeedbackEffectBase.h"
#include "GFEasing.h"
#include "GFUtilStruct.generated.h"

USTRUCT(BlueprintType)
struct GAMEFEEDBACKCORE_API FGFInterpolator
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Interpolator|Ease")
	bool bUseCustomCurve = false;

	UPROPERTY(EditAnywhere, Category = "Interpolator|Ease",
		meta = (EditCondition = "!bUseCustomCurve", EditConditionHides = true))
	EGFEaseType EaseType = EGFEaseType::Linear;

	UPROPERTY(EditAnywhere, Category = "Interpolator|Ease",
		meta = (EditCondition = "bUseCustomCurve", EditConditionHides = true))
	UCurveFloat* CustomCurve = nullptr;

	UPROPERTY(EditAnywhere, Category = "Interpolator|Remap")
	bool bUseRemap = false;

	UPROPERTY(EditAnywhere, Category = "Interpolator|Remap",
		meta = (EditCondition = "bUseRemap", EditConditionHides = true))
	float RemapMin = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Interpolator|Remap",
		meta = (EditCondition = "bUseRemap", EditConditionHides = true))
	float RemapMax = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Interpolator|Scale")
	bool bUseScale = false;

	UPROPERTY(EditAnywhere, Category = "Interpolator|Scale",
		meta = (EditCondition = "bUseScale", EditConditionHides = true))
	float Scale = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Interpolator|Offset")
	bool bUseOffset = false;

	UPROPERTY(EditAnywhere, Category = "Interpolator|Offset",
		meta = (EditCondition = "bUseOffset", EditConditionHides = true))
	float Offset = 0.0f;

private:
	float InAlpha = 0;

public:
	/**
	 * Basically, this is a Set function, and since most of its usage scenarios are internal to GF,
	 * naming it after Update makes the code a bit more readable
	 * @param Alpha Alpha value to update
	 */
	void UpdateAlpha(const float Alpha)
	{
		InAlpha = FMath::Clamp(Alpha, 0.0f, 1.0f);
	}

	float GetAlpha() const
	{
		float OutAlpha = InAlpha;

		// Ease
		if (bUseCustomCurve && CustomCurve)
		{
			OutAlpha = CustomCurve->GetFloatValue(InAlpha);
		}
		else
		{
			OutAlpha = FGFEasing::Ease(InAlpha, EaseType);
		}

		// Remap
		if (bUseRemap)
		{
			OutAlpha = FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 1.0f), FVector2D(RemapMin, RemapMax),
			                                             OutAlpha);
		}

		// Scale
		if (bUseScale)
		{
			OutAlpha *= Scale;
		}

		// Offset
		if (bUseOffset)
		{
			OutAlpha += Offset;
		}

		return OutAlpha;
	}
};

USTRUCT(BlueprintType)
struct GAMEFEEDBACKCORE_API FGFActorSelection
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "ActorSelection")
	bool bUseSelfActor = true;

	UPROPERTY(EditAnywhere, Category = "ActorSelection", DisplayName = "CustomActor",
		meta = (EditCondition = "!bUseSelfActor", EditConditionHides = true))
	TSoftObjectPtr<AActor> CustomActorSoftPtr = nullptr;

	UPROPERTY(EditAnywhere, Category = "ActorSelection")
	bool bUseRootComponent = true;

	UPROPERTY(EditAnywhere, Category = "ActorSelection",
		meta=(EditCondition = "!bUseRootComponent", EditConditionHides = true))
	TSubclassOf<UActorComponent> ComponentClass = nullptr;

	UPROPERTY(EditAnywhere, Category = "ActorSelection",
		meta=(EditCondition = "!bUseRootComponent", EditConditionHides = true))
	bool bUseComponentName = false;

	UPROPERTY(EditAnywhere, Category = "ActorSelection",
		meta=(EditCondition = "!bUseRootComponent && bUseComponentName", EditConditionHides = true))
	FName ComponentName = NAME_None;

private:
	EGameFeedbackEffectContextType ContextType = EGameFeedbackEffectContextType::Static;

	UPROPERTY()
	AActor* ContextActor = nullptr;

	UPROPERTY()
	AActor* CustomActor = nullptr;

	bool IsOnlyActorOrComponentContext() const
	{
		return ContextType == EGameFeedbackEffectContextType::Actor || ContextType ==
			EGameFeedbackEffectContextType::Component;
	}

	UPROPERTY()
	UActorComponent* TargetComponent = nullptr;

public:
	void Init(const EGameFeedbackEffectContextType InContextType, AActor* InContextActor);;

	bool IsActorValid() const;
	bool IsComponentValid();

	AActor* GetTargetActor() const;
	bool IsUseCustomTargetComponent();

	template <typename T = UActorComponent>
	T* GetTargetComponent();
};

template <typename T>
T* FGFActorSelection::GetTargetComponent()
{
	if (!IsActorValid())
	{
		return nullptr;
	}

	if (TargetComponent)
	{
		return Cast<T>(TargetComponent);
	}

	AActor* Target = GetTargetActor();
	check(Target);
	if (!bUseRootComponent)
	{
		if (!bUseComponentName)
		{
			TargetComponent = Target->GetComponentByClass(ComponentClass);
		}
		else
		{
			TArray<UActorComponent*> Components;

			Target->GetComponents(ComponentClass, Components);
			if (Components.Num() > 0)
			{
				for (auto Component : Components)
				{
					if (Component->GetName() == ComponentName)
					{
						TargetComponent = Component;
						break;
					}
				}
			}
		}
	}
	else
	{
		TargetComponent = Target->GetRootComponent();
	}
	return Cast<T>(TargetComponent);
}
