// Copyright (c) Lim Young


#include "Time/GFE_Time.h"

#include "Kismet/GameplayStatics.h"

void UGFE_Time_FreezeFrame::OnInit()
{
	Super::OnInit();

	ContextWorld = GetContextObject()->GetWorld();
}

void UGFE_Time_FreezeFrame::OnPlay()
{
	Super::OnPlay();

	if (!ContextWorld)
	{
		return;
	}

	OriginalTimeDilation = UGameplayStatics::GetGlobalTimeDilation(ContextWorld);
	UGameplayStatics::SetGlobalTimeDilation(ContextWorld, MinimumTimeDilation);
}

void UGFE_Time_FreezeFrame::OnStop(bool bInterrupted)
{
	Super::OnStop(bInterrupted);

	if (!ContextWorld)
	{
		return;
	}

	UGameplayStatics::SetGlobalTimeDilation(ContextWorld, OriginalTimeDilation);
}

void UGFE_Time_TimeFollow::OnInit()
{
	Super::OnInit();

	ContextWorld = GetContextObject()->GetWorld();
}

void UGFE_Time_TimeFollow::OnPlay()
{
	Super::OnPlay();

	if (!ContextWorld)
	{
		return;
	}

	UGameplayStatics::SetGlobalTimeDilation(ContextWorld, StartTimeDilation);
}

void UGFE_Time_TimeFollow::OnTick(float DeltaTime)
{
	Super::OnTick(DeltaTime);

	if (!ContextWorld)
	{
		return;
	}

	UGameplayStatics::SetGlobalTimeDilation(ContextWorld, FMath::Lerp(StartTimeDilation, EndTimeDilation,
	                                                                  GetInterpolatorAlpha()));
}

void UGFE_Time_TimeFollow::OnStop(bool bInterrupted)
{
	Super::OnStop(bInterrupted);

	if (!ContextWorld)
	{
		return;
	}

	if (bInterrupted && bForceEndTimeDilationWhenInterrupted)
	{
		UGameplayStatics::SetGlobalTimeDilation(ContextWorld, EndTimeDilation);
		return;
	}

	UGameplayStatics::SetGlobalTimeDilation(ContextWorld, FMath::Lerp(StartTimeDilation, EndTimeDilation,
	                                                                  GetInterpolatorAlpha()));
}
