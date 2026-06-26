// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AwarnessComponent.generated.h"

class AAI_BaseController;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_AIDIRECTOR_API UAwarnessComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAwarnessComponent();
	
	virtual void InitializeComponent() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY()
	AAI_BaseController* AICRef;
	
private:
	
	float CurrentAwarnessValue;
	float MaxAwarnessValue;
	float AwarnessDecreaseValue;
	float AwarnessDecreaseTime;
	float AwarnessPauseTime;
	float AwarnessIncreaseOnHearing;
	float AwarnessIncreaseOnSight;	
};
