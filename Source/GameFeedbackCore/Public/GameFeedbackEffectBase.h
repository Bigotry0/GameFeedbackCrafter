// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameFeedbackEffectBase.generated.h"

#define GFE_OnlyComponentContext EditCondition = "GetContextType() == EGameFeedbackEffectContextType::Component"
#define GFE_OnlyActorContext EditCondition = "GetContextType() == EGameFeedbackEffectContextType::Actor"
#define GFE_OnlyWorldContext EditCondition = "GetContextType() == EGameFeedbackEffectContextType::World"
#define GFE_OnlyStaticContext EditCondition = "GetContextType() == EGameFeedbackEffectContextType::Static"

class UGameFeedback;

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

UENUM(Flags)
enum class EGameFeedbackEffectContextType : uint8
{
	Actor,
	Component,
	World,
	Static
};

//TODO: Add Custom Editor
USTRUCT()
struct FGameFeedbackEffectBasicConfig
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Basic|Time")
	float ElapsedTime = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Basic|Time")
	float Duration = 0.2f;

	UPROPERTY(VisibleAnywhere, Category = "Basic|State")
	EGameFeedbackEffectState State = EGameFeedbackEffectState::NotInitialized;

	/**
	 * Duration / ElapsedTime
	 * @return Progress of the effect. Clamp between 0.0f and 1.0f
	 */
	float GetProgress() const
	{
		if (Duration == 0.0f)
		{
			return 1.0f;
		}

		return FMath::Clamp(ElapsedTime / Duration, 0.0f, 1.0f);
	}
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

	UGameFeedbackEffectBase();

protected:
	UPROPERTY(EditAnywhere, Category = "Basic", meta=(DisplayPriority = 1))
	FGameFeedbackEffectBasicConfig BasicConfig;

	/**
	 * Wrapper function for FGameFeedbackEffectBasicConfig::GetProgress()
	 * @return Progress of the effect. Clamp between 0.0f and 1.0f
	 */
	float GetEffectProgress() const
	{
		return BasicConfig.GetProgress();
	}

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

private:
	/**
	 * Try to get the world, follow outer chain until UWorld is found.
	 * @return UWorld if found, nullptr otherwise
	 */
	UWorld* TryGetContextWorld() const;

protected:
	/**
	 * The context type of the effect.
	 */
	UPROPERTY(VisibleAnywhere, Category = "Basic", meta=(DisplayPriority = 2))
	//TODO:Remove UPROPERTY, Now it's just for debugging
	EGameFeedbackEffectContextType ContextType;

	/**
	 * Get the owner feedback of this effect.
	 * @return Owner feedback if found, nullptr otherwise
	 */
	UGameFeedback* GetOwnerFeedback() const;

	/**
	 * Get the context type of the effect.
	 * @return Context type of the effect
	 */
	EGameFeedbackEffectContextType GetContextType() const;

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
