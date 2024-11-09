// Copyright (c) Lim Young


#include "GameFeedbackManagerComponent.h"

#include "GameFeedbackPlayer.h"

DEFINE_LOG_CATEGORY(LogGameFeedbackCrafter);

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
}

bool UGameFeedbackManagerComponent::ValidateFeedback(FName FeedbackName) const
{
	if (!Feedbacks.Contains(FeedbackName))
	{
#if WITH_EDITOR
		UE_LOG(LogGameFeedbackCrafter, Warning, TEXT("FeedbackName: %s is not found."), *FeedbackName.ToString());
#endif
		return false;
	}

	return true;
}

UGameFeedbackPlayer* UGameFeedbackManagerComponent::GetFeedbackPlayerFromFeedbacksMap(FName FeedbackName)
{
	if (!Feedbacks.Contains(FeedbackName))
	{
#if WITH_EDITOR
		UE_LOG(LogGameFeedbackCrafter, Warning, TEXT("FeedbackName is not found."));
#endif
		return nullptr;
	}

	if (!FeedbackPlayers.Contains(FeedbackName))
	{
		// Must be reset feedback. If not, the feedback effect can not initialize.
		Feedbacks[FeedbackName]->ResetFeedback();

		UGameFeedbackPlayer* FeedbackPlayer = NewObject<UGameFeedbackPlayer>(this);
		FeedbackPlayer->LoadFeedback(Feedbacks[FeedbackName], EGameFeedbackEffectContextType::Component, this);
		FeedbackPlayers.Add(FeedbackName, FeedbackPlayer);
	}

	return FeedbackPlayers[FeedbackName];
}

void UGameFeedbackManagerComponent::PlayFeedback(FName FeedbackName, EGameFeedbackPlayDirection PlayDirection)
{
	if (!ValidateFeedback(FeedbackName))
	{
		return;
	}

	UGameFeedbackPlayer* FeedbackPlayer = GetFeedbackPlayerFromFeedbacksMap(FeedbackName);
	if (FeedbackPlayer)
	{
		FeedbackPlayer->PlayFeedback(PlayDirection);
	}
}

void UGameFeedbackManagerComponent::PauseFeedback(FName FeedbackName)
{
	if (!ValidateFeedback(FeedbackName))
	{
		return;
	}

	UGameFeedbackPlayer* FeedbackPlayer = GetFeedbackPlayerFromFeedbacksMap(FeedbackName);
	if (FeedbackPlayer)
	{
		FeedbackPlayer->PauseFeedback();
	}
}

void UGameFeedbackManagerComponent::ResumeFeedback(FName FeedbackName)
{
	if (!ValidateFeedback(FeedbackName))
	{
		return;
	}

	UGameFeedbackPlayer* FeedbackPlayer = GetFeedbackPlayerFromFeedbacksMap(FeedbackName);
	if (FeedbackPlayer)
	{
		FeedbackPlayer->ResumeFeedback();
	}
}

void UGameFeedbackManagerComponent::StopFeedback(FName FeedbackName)
{
	if (!ValidateFeedback(FeedbackName))
	{
		return;
	}

	UGameFeedbackPlayer* FeedbackPlayer = GetFeedbackPlayerFromFeedbacksMap(FeedbackName);
	if (FeedbackPlayer)
	{
		FeedbackPlayer->StopFeedback();
	}
}

void UGameFeedbackManagerComponent::ReplayFeedback(FName FeedbackName, EGameFeedbackPlayDirection PlayDirection)
{
	if (!ValidateFeedback(FeedbackName))
	{
		return;
	}

	UGameFeedbackPlayer* FeedbackPlayer = GetFeedbackPlayerFromFeedbacksMap(FeedbackName);
	if (FeedbackPlayer)
	{
		FeedbackPlayer->ReplayFeedback(PlayDirection);
	}
}

// #if WITH_EDITOR
// void UGameFeedbackManagerComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
// {
	// if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UGameFeedbackManagerComponent, Feedbacks))
	// {
	// 	const int32 ChangeIndex = PropertyChangedEvent.GetArrayIndex(
	// 		(GET_MEMBER_NAME_CHECKED(UGameFeedbackManagerComponent, Feedbacks)).ToString());
	//
	// 	TArray<FName> FeedbacksKeyArray;
	// 	Feedbacks.GenerateKeyArray(FeedbacksKeyArray);
	//
	// 	if (!FeedbacksKeyArray.IsValidIndex(ChangeIndex))
	// 	{
	// 		return;
	// 	}
	//
	// 	const FName FeedbackName = FeedbacksKeyArray[ChangeIndex];
	//
	// 	if (FeedbackPlayers.Contains(FeedbackName))
	// 	{
	// 		ReplayFeedback(FeedbackName, Feedbacks[FeedbackName]->GetPlayDirection());
	// 	}
	// }
	//
	// Super::PostEditChangeProperty(PropertyChangedEvent);
// }
// #endif
