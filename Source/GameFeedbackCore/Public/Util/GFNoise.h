// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "ThirdParty/FastNoiseLite.h"
#include "GFNoise.generated.h"

UENUM(BlueprintType)
enum class EGFNoiseType : uint8
{
	OpenSimplex2,
	OpenSimplex2S,
	Cellular,
	Perlin,
	ValueCubic,
	Value
};

/**
 * Noise generator.
 */
USTRUCT(BlueprintType)
struct GAMEFEEDBACKCORE_API FGFNoise
{
	GENERATED_BODY()

private:
	TSharedPtr<FastNoiseLite> Noise = MakeShared<FastNoiseLite>();

public:
	FGFNoise();

protected:
	/**
	 * Noise type.
	 */
	UPROPERTY(EditAnywhere, Category = "Noise")
	EGFNoiseType NoiseType = EGFNoiseType::Perlin;

	/**
	 * Whether to use a random seed.
	 */
	UPROPERTY(EditAnywhere, Category = "Noise")
	bool bUseRandomSeed = true;

	/**
	 * Seed value. Default is 1337.
	 */
	UPROPERTY(EditAnywhere, Category = "Noise", meta = (EditCondition = "!bUseRandomSeed", EditConditionHides = true))
	int32 Seed = 1337;

	/**
	 * The size of the generated noise.
	 * When tuning the parameter, it can be simply understood that the larger the value, the higher the frequency.
	 * And the smaller the value, the lower the frequency.
	 */
	UPROPERTY(EditAnywhere, Category = "Noise")
	int32 SampleAccuracy = 64;

	/**
	 * The direction of the noise sample.
	 * This value generally does not need to be adjusted,
	 * and directly adjusting this value is in fact basically equivalent to directly adjusting the noise seed.
	 * 
	 * TODO: Slide this value to achieve special noise effects
	 */
	UPROPERTY(EditAnywhere, Category = "Noise", meta = (UIMin = "-360.0", UIMax = "360.0"))
	float SampleDirectionOffsetAngle = 0;

	/**
	 * The scale of the noise.
	 */
	UPROPERTY(EditAnywhere, Category = "Noise")
	float Scale = 1.0f;

	/**
	 * Whether to ignore the X when return the result.
	 */
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Noise")
	bool bIgnoreX = false;

	/**
	 * Whether to ignore the Y when return the result.
	 */
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Noise")
	bool bIgnoreY = false;

	/**
	 * Whether to ignore the Z when return the result.
	 */
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Noise")
	bool bIgnoreZ = false;

private:
	FVector2d SampleDirection;

public:
	float GetNoise1D(const float Alpha) const;
	FVector2d GetNoise2D(const float Alpha) const;
	FVector GetNoise3D(const float Alpha) const;

private:
	void UpdateSampleDirection();
	void UpdateNoiseType() const;

public:
	void UpdateNoise();

private:
	void CalculateSamplePosition(const float Alpha, float& X, float& Y) const;
	void CalculateSamplePosition(const float Alpha, float& X, float& Y, float& Z) const;
};
