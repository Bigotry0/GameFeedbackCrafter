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

void UGameFeedbackPlayer::LoadFeedback(UGameFeedback* Feedback, const EGameFeedbackEffectContextType ContextType,
                                       UObject* Context)
{
	CurrentFeedback = Feedback;

	if (!IsCurrentFeedbackValid())
	{
		return;
	}

	CurrentFeedback->OnGameFeedbackStateChanged.AddDynamic(this, &UGameFeedbackPlayer::OnGameFeedbackStateChanged);
	CurrentFeedback->OnGameFeedbackStopped.AddDynamic(this, &UGameFeedbackPlayer::OnGameFeedbackStopped);
	CurrentFeedback->InitFeedback(ContextType, Context);
}

void UGameFeedbackPlayer::PlayFeedback(const EGameFeedbackPlayDirection PlayDirection, bool bUseAutoUnload)
{
	if (!IsCurrentFeedbackValid())
	{
		return;
	}

	bAutoUnload = bUseAutoUnload;
	CurrentFeedback->PlayFeedback(PlayDirection);
}

void UGameFeedbackPlayer::PauseFeedback() const
{
	if (!IsCurrentFeedbackValid())
	{
		return;
	}

	CurrentFeedback->PauseFeedback();
}

void UGameFeedbackPlayer::ResumeFeedback() const
{
	if (!IsCurrentFeedbackValid())
	{
		return;
	}

	CurrentFeedback->ResumeFeedback();
}

void UGameFeedbackPlayer::StopFeedback() const
{
	if (!IsCurrentFeedbackValid())
	{
		return;
	}

	CurrentFeedback->StopFeedback();
}

void UGameFeedbackPlayer::ReplayFeedback(const EGameFeedbackPlayDirection PlayDirection, bool bUseAutoUnload)
{
	if (!IsCurrentFeedbackValid())
	{
		return;
	}

	CurrentFeedback->StopFeedback();

	bAutoUnload = bUseAutoUnload;
	CurrentFeedback->PlayFeedback(PlayDirection);
}

void UGameFeedbackPlayer::UnloadFeedback()
{
	if (!IsCurrentFeedbackValid())
	{
		return;
	}

	CurrentFeedback->OnGameFeedbackStateChanged.RemoveDynamic(this, &UGameFeedbackPlayer::OnGameFeedbackStateChanged);
	CurrentFeedback->OnGameFeedbackStopped.RemoveDynamic(this, &UGameFeedbackPlayer::OnGameFeedbackStopped);
	CurrentFeedback = nullptr;
}

void UGameFeedbackPlayer::ResetFeedback()
{
	if (!IsCurrentFeedbackValid())
	{
		return;
	}

	CurrentFeedback->ResetFeedback();
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

bool UGameFeedbackPlayer::IsCurrentFeedbackValid() const
{
	return CurrentFeedback != nullptr;
}

bool UGameFeedbackPlayer::IsRunning() const
{
	return bIsRunning;
}
