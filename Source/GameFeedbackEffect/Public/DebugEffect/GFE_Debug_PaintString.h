// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "GameFeedbackEffectBase.h"
#include "GFE_Debug_PaintString.generated.h"

UENUM(BlueprintType)
enum class EGFE_Debug_PaintString_Timing : uint8
{
	OnInit,
	OnPlay,
	OnPause,
	OnResume,
	OnStop,
	OnTick
};

/**
 * 
 */
UCLASS()
class UGFE_Debug_PaintString : public UGameFeedbackEffectBase
{
	GENERATED_BODY()

public:
	/**
	 * The text to be displayed on screen.
	 */
	UPROPERTY(EditAnywhere, Category="DebugEffect")
	FString Text = "Text";

	/**
	 * The duration for which the text will be displayed on screen.
	 */
	UPROPERTY(EditAnywhere, Category="DebugEffect")
	float TextDuration = 1.0f;

	UPROPERTY(EditAnywhere, Category="DebugEffect")
	FColor Color = FColor::White;

	/**
	 * Whether to specify the Key of the printed text
	 */
	UPROPERTY(EditAnywhere, Category = "DebugEffect")
	bool bUseKey = false;

	/**
	 * The key used to identify the printed text.
	 */
	UPROPERTY(EditAnywhere, Category = "DebugEffect", meta = (EditCondition = "bUseKey", EditConditionHides = true))
	FName Key;

	/**
	 * Determines when the text should be painted on the screen.
	 */
	UPROPERTY(EditAnywhere, Category = "DebugEffect")
	EGFE_Debug_PaintString_Timing Timing = EGFE_Debug_PaintString_Timing::OnInit;

	/**
	 * Whether to show the text when the effect is interrupted
	 */
	UPROPERTY(EditAnywhere, Category = "DebugEffect",
		meta = (EditCondition = "Timing == EGFE_Debug_PaintString_Timing::OnStop", EditConditionHides = true))
	bool bShowInterrupted = true;

protected:
	virtual void OnInit() override;
	virtual void OnPlay() override;
	virtual void OnPause() override;
	virtual void OnResume() override;
	virtual void OnStop(bool bInterrupted) override;
	virtual void OnTick(float DeltaTime) override;

#if WITH_EDITOR

protected:
	virtual EGameFeedbackEffectType GetEffectType() const override
	{
		return EGameFeedbackEffectType::Debug;
	}
#endif
};
