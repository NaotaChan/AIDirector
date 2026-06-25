// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AISenseConfig_Heat.h"
#include "AI/AISense_Heat.h"


UAISenseConfig_Heat::UAISenseConfig_Heat(const FObjectInitializer& ObjectInitializer)
{
	SuccessDebugColor = FColor::Green;
	DebugColor = SuccessDebugColor;
	FailDebugColor = FColor::Red;
	Implementation = GetSenseImplementation();
}


TSubclassOf<UAISense> UAISenseConfig_Heat::GetSenseImplementation() const
{
	return UAISense_Heat::StaticClass();
}

