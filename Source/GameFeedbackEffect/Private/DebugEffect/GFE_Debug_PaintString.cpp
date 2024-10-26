// Copyright (c) Lim Young

#include "DebugEffect/GFE_Debug_PaintString.h"


void UGFE_Debug_PaintString::OnInit()
{
	if (Timing == EGFE_Debug_PaintString_Timing::OnInit)
	{
		// Paint
		GEngine->AddOnScreenDebugMessage(bUseKey ? Key.ToUnstableInt() : -1
		                                 , TextDuration, Color, Text);
	}
}

void UGFE_Debug_PaintString::OnPlay()
{
	if (Timing == EGFE_Debug_PaintString_Timing::OnPlay)
	{
		// Paint
		GEngine->AddOnScreenDebugMessage(bUseKey ? Key.ToUnstableInt() : -1
		                                 , TextDuration, Color, Text);
	}
}

void UGFE_Debug_PaintString::OnPause()
{
	if (Timing == EGFE_Debug_PaintString_Timing::OnPause)
	{
		// PaintF
		GEngine->AddOnScreenDebugMessage(bUseKey ? Key.ToUnstableInt() : -1
		                                 , TextDuration, Color, Text);
	}
}

void UGFE_Debug_PaintString::OnResume()
{
	if (Timing == EGFE_Debug_PaintString_Timing::OnResume)
	{
		// Paint
		GEngine->AddOnScreenDebugMessage(bUseKey ? Key.ToUnstableInt() : -1
		                                 , TextDuration, Color, Text);
	}
}

void UGFE_Debug_PaintString::OnStop(bool bInterrupted)
{
	if (Timing == EGFE_Debug_PaintString_Timing::OnStop)
	{
		// Paint
		GEngine->AddOnScreenDebugMessage(bUseKey ? Key.ToUnstableInt() : -1
		                                 , TextDuration, Color, Text);

		if (!bShowInterrupted)
		{
			return;
		}

		if (bInterrupted)
		{
			GEngine->AddOnScreenDebugMessage(bUseKey ? Key.ToUnstableInt() : -1
			                                 , TextDuration, Color, TEXT("Interrupted"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(bUseKey ? Key.ToUnstableInt() : -1
			                                 , TextDuration, Color, TEXT("Finished"));
		}
	}
}

void UGFE_Debug_PaintString::OnTick(float DeltaTime)
{
	if (Timing == EGFE_Debug_PaintString_Timing::OnTick)
	{
		// Paint
		GEngine->AddOnScreenDebugMessage(bUseKey ? Key.ToUnstableInt() : -1
		                                 , TextDuration, Color, Text);
	}
}

EGameFeedbackEffectType UGFE_Debug_PaintString::GetEffectType() const
{
	return EGameFeedbackEffectType::Debug;
}
