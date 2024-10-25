// Copyright (c) Lim Young


#include "GameFeedbackFactory.h"

#include "GameFeedback.h"

UGameFeedbackFactory::UGameFeedbackFactory()
{
	SupportedClass = UGameFeedback::StaticClass();
	bCreateNew = true;
}

UObject* UGameFeedbackFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
                                                UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UGameFeedback>(InParent, InClass, InName, Flags, Context);
}
