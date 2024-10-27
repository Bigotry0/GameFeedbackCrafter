// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "GFEasing.h"
#include "GFUtilStruct.generated.h"

USTRUCT(BlueprintType)
struct FGFInterpolator
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
