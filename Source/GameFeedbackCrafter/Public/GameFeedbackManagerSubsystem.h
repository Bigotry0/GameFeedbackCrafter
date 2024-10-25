// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "GameFeedbackManagerInterface.h"
#include "UObject/Object.h"
#include "GameFeedbackManagerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class GAMEFEEDBACKCRAFTER_API UGameFeedbackManagerSubsystem : public UWorldSubsystem, public IGameFeedbackManagerInterface
{
	GENERATED_BODY()
};
