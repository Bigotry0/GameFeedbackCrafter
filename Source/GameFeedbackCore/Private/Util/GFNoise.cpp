// Copyright (c) Lim Young


#include "Util/GFNoise.h"

FGFNoise::FGFNoise()
{
	UpdateNoise();
}

float FGFNoise::GetNoise1D(const float Alpha) const
{
	float X, Y;
	CalculateSamplePosition(Alpha, X, Y);

	return Noise->GetNoise(X, Y) * Scale * !bIgnoreX;
}

FVector2d FGFNoise::GetNoise2D(const float Alpha) const
{
	float X, Y;
	CalculateSamplePosition(Alpha, X, Y);

	return FVector2d(Noise->GetNoise(X, Y) * !bIgnoreX, Noise->GetNoise(Y, X) * !bIgnoreY) * Scale;
}

FVector FGFNoise::GetNoise3D(const float Alpha) const
{
	float X, Y, Z;
	CalculateSamplePosition(Alpha, X, Y, Z);

	return FVector(Noise->GetNoise(X, Y) * !bIgnoreX, Noise->GetNoise(Y, X) * !bIgnoreY,
	               Noise->GetNoise(0.0f, 0.0f, Z) * !bIgnoreZ) * Scale;
}

void FGFNoise::UpdateSampleDirection()
{
	SampleDirection = FVector2d(FMath::Cos(SampleDirectionOffsetAngle), FMath::Sin(SampleDirectionOffsetAngle));
}

void FGFNoise::UpdateNoiseType() const
{
	switch (NoiseType)
	{
	case EGFNoiseType::OpenSimplex2:
		Noise->SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
		break;
	case EGFNoiseType::OpenSimplex2S:
		Noise->SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
		break;
	case EGFNoiseType::Cellular:
		Noise->SetNoiseType(FastNoiseLite::NoiseType_Cellular);
		break;
	case EGFNoiseType::Perlin:
		Noise->SetNoiseType(FastNoiseLite::NoiseType_Perlin);
		break;
	case EGFNoiseType::ValueCubic:
		Noise->SetNoiseType(FastNoiseLite::NoiseType_ValueCubic);
		break;
	case EGFNoiseType::Value:
		Noise->SetNoiseType(FastNoiseLite::NoiseType_Value);
		break;
	}
}

void FGFNoise::UpdateNoise()
{
	if (bUseRandomSeed)
	{
		Noise->SetSeed(FMath::Rand());
	}
	else
	{
		Noise->SetSeed(Seed);
	}

	UpdateNoiseType();
	UpdateSampleDirection();
}

void FGFNoise::CalculateSamplePosition(const float Alpha, float& X, float& Y) const
{
	float SampleAccuracyHalf = SampleAccuracy * 0.5;
	FVector2d SampleStart = -SampleDirection * 0.5 * SampleAccuracyHalf;
	FVector2d SampleEnd = SampleDirection * 0.5 * SampleAccuracyHalf;

	X = FMath::Lerp(SampleStart.X, SampleEnd.X, Alpha);
	Y = FMath::Lerp(SampleStart.Y, SampleEnd.Y, Alpha);
}

void FGFNoise::CalculateSamplePosition(const float Alpha, float& X, float& Y, float& Z) const
{
	float SampleAccuracyHalf = SampleAccuracy * 0.5;
	FVector2d SampleStart = -SampleDirection * 0.5 * SampleAccuracyHalf;
	FVector2d SampleEnd = SampleDirection * 0.5 * SampleAccuracyHalf;

	X = FMath::Lerp(SampleStart.X, SampleEnd.X, Alpha);
	Y = FMath::Lerp(SampleStart.Y, SampleEnd.Y, Alpha);

	Z = FMath::Lerp(-0.5f, 0.5f, Alpha) * SampleAccuracyHalf;
}
