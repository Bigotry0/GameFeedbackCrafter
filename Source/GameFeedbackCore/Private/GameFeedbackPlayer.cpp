// Copyright (c) Lim Young

#include "GameFeedbackPlayer.h"

void UGameFeedbackPlayer::OnGameFeedbackStateChanged(EGameFeedbackState NewState)
{
	if (NewState == EGameFeedbackState::Running)
	{
		bIsRunning = true;
	}
	else
	{
		bIsRunning = false;
	}
}

void UGameFeedbackPlayer::OnGameFeedbackStopped(bool bInterrupted)
{
	if (bAutoUnload)
	{
		UnloadFeedback();
	}
}

void UGameFeedbackPlayer::LoadFeedback(UGameFeedback* Feedback)
{
	CurrentFeedback = Feedback;

	CurrentFeedback->OnGameFeedbackStateChanged.AddDynamic(this, &UGameFeedbackPlayer::OnGameFeedbackStateChanged);
	CurrentFeedback->OnGameFeedbackStopped.AddDynamic(this, &UGameFeedbackPlayer::OnGameFeedbackStopped);
	CurrentFeedback->InitFeedback();
}

void UGameFeedbackPlayer::PlayFeedback(bool bUseAutoUnload)
{
	bAutoUnload = bUseAutoUnload;
	CurrentFeedback->PlayFeedback();
}

void UGameFeedbackPlayer::PauseFeedback() const
{
	CurrentFeedback->PauseFeedback();
}

void UGameFeedbackPlayer::ResumeFeedback() const
{
	CurrentFeedback->ResumeFeedback();
}

void UGameFeedbackPlayer::StopFeedback() const
{
	CurrentFeedback->StopFeedback();
}

void UGameFeedbackPlayer::ReplayFeedback() const
{
	CurrentFeedback->StopFeedback();
	CurrentFeedback->PlayFeedback();
}

void UGameFeedbackPlayer::UnloadFeedback()
{
	CurrentFeedback->OnGameFeedbackStateChanged.RemoveDynamic(this, &UGameFeedbackPlayer::OnGameFeedbackStateChanged);
	CurrentFeedback->OnGameFeedbackStopped.RemoveDynamic(this, &UGameFeedbackPlayer::OnGameFeedbackStopped);
	CurrentFeedback = nullptr;
}

TStatId UGameFeedbackPlayer::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UGameFeedbackPlayer, STATGROUP_Tickables);
}

void UGameFeedbackPlayer::Tick(float DeltaTime)
{
	if (bIsRunning)
	{
		CurrentFeedback->TickFeedback(DeltaTime);
	}
}
