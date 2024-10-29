// Copyright (c) Lim Young


#include "Util/GFUtilStruct.h"

void FGFActorSelection::Init(const EGameFeedbackEffectContextType InContextType, AActor* InContextActor)
{
	ContextType = InContextType;
	ContextActor = InContextActor;

	if(!bUseSelfActor)
	{
		// Get RunTime Actor
		CustomActor = CustomActorSoftPtr.Get();
	}
}

bool FGFActorSelection::IsActorValid() const
{
	bool bValid = false;

	if (bUseSelfActor)
	{
		if (ContextActor)
		{
			bValid = true;
		}
	}
	else
	{
		if (CustomActorSoftPtr.IsValid())
		{
			bValid = true;
		}
	}

	return bValid;
}

bool FGFActorSelection::IsComponentValid()
{
	bool bValid = false;

	if (!TargetComponent)
	{
		GetTargetComponent();
	}

	if (TargetComponent)
	{
		bValid = true;
	}

	return bValid;
}

AActor* FGFActorSelection::GetTargetActor() const
{
	if (bUseSelfActor)
	{
		return ContextActor;
	}

	return CustomActor;
}

bool FGFActorSelection::IsUseCustomTargetComponent()
{
	if (!IsActorValid())
	{
		return false;
	}

	if (bUseRootComponent)
	{
		return false;
	}

	if (!IsComponentValid())
	{
		return false;
	}

	return true;
}
