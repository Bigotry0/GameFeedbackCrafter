// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameFeedbackEffectBase.generated.h"

UENUM()
enum class EGameFeedbackEffectType : uint8
{
	Audio = 0,
	VFX = 1,
	Transform = 2,
	Camera = 3,
	PostProcess = 4,
	Logic = 5,
	Time = 6,
	Haptic = 7,
	UMG = 8,
	Light = 9,
	Actor = 10,
	Material = 11,
	Animation = 12,
	Event = 13,
	Debug = 14,
	/* Add custom types below */

	Custom = 26
};

UENUM(BlueprintType)
enum class EGameFeedbackEffectState : uint8
{
	NotInitialized,
	Idle,
	Running,
	Paused,
};

//TODO: Add Custom Editor
USTRUCT()
struct FGameFeedbackEffectBasicConfig
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Basic")
	float ElapsedTime = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Basic")
	float Duration = 0.2f;

	UPROPERTY(VisibleAnywhere, Category = "Basic")
	EGameFeedbackEffectState State = EGameFeedbackEffectState::NotInitialized;
};

static FColor GetTypeColor(EGameFeedbackEffectType Type)
{
	uint8 TypeIndex = static_cast<uint8>(Type);

	/* 3 segments */
	constexpr uint8 SegmentCount = 3;
	constexpr uint8 Unit = 255 / SegmentCount;

	FVector Color = FVector(0.0f, 0.0f, 0.0f);
	for (uint8 i = 0; i < 3 /* Vector Dimension */; i++)
	{
		const uint8 ChannelValue = (TypeIndex % SegmentCount + 1) * Unit;
		Color[i] = ChannelValue;

		TypeIndex /= SegmentCount;
		if (TypeIndex == 0)
		{
			break;
		}
	}

	return FColor(Color.X, Color.Y, Color.Z);
}

UCLASS(Abstract, EditInlineNew, AutoExpandCategories=(Basic))
class GAMEFEEDBACKCORE_API UGameFeedbackEffectBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Basic", meta=(DisplayPriority = 0))
	FColor EffectTypeColor;

	UGameFeedbackEffectBase()
	{
#if WITH_EDITOR
		EffectTypeColor = GetTypeColor(GetEffectTypeFromChildClass());
#endif
	}

protected:
	UPROPERTY(EditAnywhere, Category = "Basic", meta=(DisplayPriority = 1))
	FGameFeedbackEffectBasicConfig BasicConfig;

#if WITH_EDITOR
	virtual EGameFeedbackEffectType GetEffectType() const
	{
		return EGameFeedbackEffectType::Custom;
	}

	EGameFeedbackEffectType GetEffectTypeFromChildClass() const
	{
		return GetEffectType();
	}
#endif

public:
	void Init();

	void Play();

	void Pause();

	void Resume();

	void Stop();

	bool Tick(float DeltaTime);

protected:
	// Life cycle
	virtual void OnInit()
	{
	}

	virtual void OnPlay()
	{
	}

	virtual void OnPause()
	{
	}

	virtual void OnResume()
	{
	}

	virtual void OnStop(bool bInterrupted)
	{
	}

	virtual void OnTick(float DeltaTime)
	{
	}
};
