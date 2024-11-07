// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameFeedbackEffectBase.generated.h"

#define GFE_OnlyComponentContext "IsOnlyComponentContext()"
#define GFE_OnlyActorContext "IsOnlyActorContext()"
#define GFE_OnlyWorldContext "IsOnlyWorldContext()"
#define GFE_OnlyStaticContext "IsOnlyStaticContext()"
#define GFE_OnlyActorOrComponentContext "IsOnlyActorOrComponentContext()"
#define GFE_ExcludeStaticContext "IsExcludeStaticContext()"

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
	Delay,
	Cooldown,
	Paused,
};

UENUM(Flags)
enum class EGameFeedbackEffectContextType : uint8
{
	Static,
	Actor,
	Component,
	World
};

UENUM(BlueprintType)
enum class ETimeScaleMode : uint8
{
	Scaled,
	Unscaled
};

USTRUCT()
struct FGameFeedbackEffectTiming
{
	GENERATED_BODY()

private:
	uint32 RepeatCount = 0;

public:
	UPROPERTY(VisibleAnywhere, Category = "Time")
	float ElapsedTime = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Time")
	float Duration = 0.2f;

	UPROPERTY(EditAnywhere, Category = "Time|TimeScale")
	ETimeScaleMode TimeScaleMode = ETimeScaleMode::Scaled;

	UPROPERTY(EditAnywhere, Category = "Time|Delay")
	float Delay = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Time|Delay")
	float CoolDown = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Time|Repeat")
	uint32 NumOfRepeats = 0;

	UPROPERTY(EditAnywhere, Category = "Time|Repeat")
	bool bRepeatForever = false;

	UPROPERTY(EditAnywhere, Category = "Time|Repeat")
	float DelayBetweenRepeats = 1.0f;

	/**
	 * Tick the timing.
	 * @param DeltaTime The time since the last tick.
	 * @param TimeDilation The time dilation value of the world.
	 * @return true if the effect is still running, false otherwise
	 */
	bool Tick(float DeltaTime, float TimeDilation)
	{
		if (Duration == 0.0f)
		{
			return false;
		}

		const float DeltaTimeScaled = TimeScaleMode == ETimeScaleMode::Scaled ? DeltaTime * TimeDilation : DeltaTime;
		ElapsedTime += DeltaTimeScaled;

		return !(ElapsedTime >= Duration);
	}

	/**
	 * Reset the timing.
	 */
	void Reset()
	{
		if (Delay > 0.0f)
		{
			ElapsedTime = -Delay;
		}
		else
		{
			ElapsedTime = 0.0f;
		}
	}

	/**
	 * Force reset the timing to zero.
	 */
	void ResetToZero()
	{
		ElapsedTime = 0.0f;
	}

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

	bool IsUseDelay() const
	{
		return Delay > 0.0f;
	}

	bool IsOnDelay() const
	{
		return ElapsedTime < 0.0f;
	}

	bool IsUseCoolDown() const
	{
		return CoolDown > 0.0f;
	}

	bool IsOnCoolDown() const
	{
		return IsUseCoolDown() && ElapsedTime >= Duration;
	}

	bool IsCoolDownEnd() const
	{
		return ElapsedTime >= Duration + CoolDown;
	}

	void ResetAtEnd()
	{
		ElapsedTime = Duration;
	}
};

//TODO: Add Custom Editor
USTRUCT()
struct FGameFeedbackEffectBasicConfig
{
	GENERATED_BODY()

private:
	bool bShouldPlayAfterCooldown = false;

public:
	UPROPERTY(EditAnywhere, Category = "Basic|Time")
	FGameFeedbackEffectTiming Timing;

	UPROPERTY(VisibleAnywhere, Category = "Basic|State")
	EGameFeedbackEffectState State = EGameFeedbackEffectState::NotInitialized;

	/**
	 * Wrapper function for FGameFeedbackEffectTiming::GetProgress()
	 * @return Progress of the effect. Clamp between 0.0f and 1.0f
	 */
	float GetProgress() const
	{
		return Timing.GetProgress();
	}

	bool ShouldPlayAfterCooldown() const
	{
		return bShouldPlayAfterCooldown;
	}

	void SetShouldPlayAfterCooldown(bool bShouldPlay)
	{
		bShouldPlayAfterCooldown = bShouldPlay;
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

	// UGameFeedbackEffectBase();

protected:
	UPROPERTY(EditAnywhere, Category = "Basic", meta=(DisplayPriority = 1))
	FGameFeedbackEffectBasicConfig BasicConfig;

	/**
	 * Wrapper function for FGameFeedbackEffectBasicConfig::GetProgress()
	 * @return Progress of the effect. Clamp between 0.0f and 1.0f
	 */
	float GetEffectProgress() const;

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

	///////////// Context /////////////
#pragma region Context

private:
	UPROPERTY()
	UGameFeedback* OwnerGameFeedback;
	/**
	 * The context type of the effect.
	 */
	UPROPERTY(VisibleAnywhere, Category = "Basic", meta=(DisplayPriority = 2))
	//TODO:Remove UPROPERTY, Now it's just for debugging
	EGameFeedbackEffectContextType ContextType;

	UPROPERTY()
	UObject* ContextObject;

	/**
     * Try to get the world, follow the context object outer chain to find the world.
     * If the context object is nullptr, follow this GFE outer chain to find the world.
     * @return UWorld if found, nullptr otherwise
     */
	UWorld* TryGetContextWorld() const;

protected:
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

	/**
	 * Get the context object of the effect.
	 * @return Context object of the effect
	 */
	UObject* GetContextObject() const;

	AActor* GetContextActor() const;

	bool IsOnlyComponentContext() const;
	bool IsOnlyActorContext() const;
	bool IsOnlyWorldContext() const;
	bool IsOnlyStaticContext() const;
	bool IsOnlyActorOrComponentContext() const;
	bool IsExcludeStaticContext() const;
#pragma endregion
	//////////////// Life cycle ////////////////
#pragma region LifeCycle

public:
	void Init(UGameFeedback* InGameFeedback, const EGameFeedbackEffectContextType InContextType,
	          UObject* InContextObject);

	void Play();

	void Pause();

	void Resume();

	/**
	 * Stop the effect.
	 * @return true if the effect successfully stopped, false the effect in cooldown or ready to cooldown.
	 */
	void Stop(bool& bOnCooldown);

	bool Tick(float DeltaTime);

	void Reset();

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

private:
	bool InIdleOrNotInitializedState() const;
#pragma endregion
	//////////////// Timing ////////////////
#pragma region Timing

private:
	UPROPERTY()
	AWorldSettings* ContextWorldSettings = nullptr;

	float GetContextWorldTimeDilation() const;
#pragma endregion
};
