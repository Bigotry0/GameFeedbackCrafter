// Copyright (c) Lim Young


#include "GameFeedbackManagerComponent.h"

#include "GameFeedbackPlayer.h"


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

	// Initialize Feedbacks
	for (auto& Feedback : Feedbacks)
	{
		Feedback.Value->InitFeedback();
	}
}

bool UGameFeedbackManagerComponent::ValidateFeedback(FName FeedbackName) const
{
	if (!Feedbacks.Contains(FeedbackName))
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("FeedbackName is not found."));
#endif
		return false;
	}

	return true;
}

UGameFeedbackPlayer* UGameFeedbackManagerComponent::GetFeedbackPlayerFromFeedbacksMap(FName FeedbackName)
{
	if (!FeedbackPlayers.Contains(FeedbackName))
	{
		FeedbackPlayers.Add(FeedbackName, NewObject<UGameFeedbackPlayer>(this));
	}

	return FeedbackPlayers[FeedbackName];
}

void UGameFeedbackManagerComponent::PlayFeedback(FName FeedbackName)
{
	if (!ValidateFeedback(FeedbackName))
	{
		return;
	}

	UGameFeedbackPlayer* FeedbackPlayer = GetFeedbackPlayerFromFeedbacksMap(FeedbackName);
	FeedbackPlayer->LoadFeedback(Feedbacks[FeedbackName]);
	FeedbackPlayer->PlayFeedback();
}

void UGameFeedbackManagerComponent::PauseFeedback(FName FeedbackName)
{
	if (!ValidateFeedback(FeedbackName))
	{
		return;
	}

	UGameFeedbackPlayer* FeedbackPlayer = GetFeedbackPlayerFromFeedbacksMap(FeedbackName);
	FeedbackPlayer->PauseFeedback();
}

void UGameFeedbackManagerComponent::ResumeFeedback(FName FeedbackName)
{
	if (!ValidateFeedback(FeedbackName))
	{
		return;
	}

	UGameFeedbackPlayer* FeedbackPlayer = GetFeedbackPlayerFromFeedbacksMap(FeedbackName);
	FeedbackPlayer->ResumeFeedback();
}

void UGameFeedbackManagerComponent::StopFeedback(FName FeedbackName)
{
	if (!ValidateFeedback(FeedbackName))
	{
		return;
	}

	UGameFeedbackPlayer* FeedbackPlayer = GetFeedbackPlayerFromFeedbacksMap(FeedbackName);
	FeedbackPlayer->StopFeedback();
}

void UGameFeedbackManagerComponent::ReplayFeedback(FName FeedbackName)
{
	if (!ValidateFeedback(FeedbackName))
	{
		return;
	}

	UGameFeedbackPlayer* FeedbackPlayer = GetFeedbackPlayerFromFeedbacksMap(FeedbackName);
	FeedbackPlayer->ReplayFeedback();
}
