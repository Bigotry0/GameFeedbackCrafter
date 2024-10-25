// Copyright (c) Lim Young

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "GameFeedbackFactory.generated.h"

/**
 * 
 */
UCLASS()
class GAMEFEEDBACKEDITOR_API UGameFeedbackFactory : public UFactory
{
	GENERATED_BODY()

public:
	UGameFeedbackFactory();

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	                                  UObject* Context, FFeedbackContext* Warn) override;
};
