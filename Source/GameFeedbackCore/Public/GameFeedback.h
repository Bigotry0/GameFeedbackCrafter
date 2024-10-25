// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "UObject/Object.h"
#include "GameFeedback.generated.h"

/**
 * 
 */
UCLASS()
class GAMEFEEDBACKCORE_API UGameFeedback : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "GameFeedback",
		meta = (BaseStruct = "/Script/GameFeedbackCore.FGameFeedbackEffectBase", ExcludeBaseStruct))
	TArray<FInstancedStruct> GameFeedbackEffects;
};
