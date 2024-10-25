// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameFeedback.h"
#include "GameFeedbackManagerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class GAMEFEEDBACKCRAFTER_API UGameFeedbackManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameFeedbackManager")
	TMap<FName, UGameFeedback*> Feedbacks;
};
