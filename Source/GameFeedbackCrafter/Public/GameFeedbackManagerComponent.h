// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "GameFeedback.h"
#include "GameFeedbackPlayer.h"
#include "Components/ActorComponent.h"
#include "GameFeedbackManagerComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAMEFEEDBACKCRAFTER_API UGameFeedbackManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGameFeedbackManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameFeedbackManager")
	TMap<FName, UGameFeedback*> Feedbacks;

private:
	UPROPERTY()
	TMap<FName, UGameFeedbackPlayer*> FeedbackPlayers;

private:
	bool ValidateFeedback(FName FeedbackName) const;

	UGameFeedbackPlayer* GetFeedbackPlayerFromFeedbacksMap(FName FeedbackName);

public:
	UFUNCTION(BlueprintCallable, Category = "GameFeedbackManager")
	void PlayFeedback(FName FeedbackName);

	UFUNCTION(BlueprintCallable, Category = "GameFeedbackManager")
	void PauseFeedback(FName FeedbackName);

	UFUNCTION(BlueprintCallable, Category = "GameFeedbackManager")
	void ResumeFeedback(FName FeedbackName);

	UFUNCTION(BlueprintCallable, Category = "GameFeedbackManager")
	void StopFeedback(FName FeedbackName);

	UFUNCTION(BlueprintCallable, Category = "GameFeedbackManager")
	void ReplayFeedback(FName FeedbackName);
};
