// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "GameFeedbackManagerInterface.h"
#include "Components/ActorComponent.h"
#include "GameFeedbackManagerComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAMEFEEDBACKCRAFTER_API UGameFeedbackManagerComponent : public UActorComponent, IGameFeedbackManagerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGameFeedbackManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
