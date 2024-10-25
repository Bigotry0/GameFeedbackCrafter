// Copyright (c) Lim Young


#include "GameFeedbackManagerComponent.h"


// Sets default values for this component's properties
UGameFeedbackManagerComponent::UGameFeedbackManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGameFeedbackManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGameFeedbackManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                  FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

