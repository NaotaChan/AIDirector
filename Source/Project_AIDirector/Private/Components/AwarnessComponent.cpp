// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AwarnessComponent.h"
#include "AI/AI_BaseController.h"
#include "Components/AlertComponent.h"



// Sets default values for this component's properties
UAwarnessComponent::UAwarnessComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	bAutoActivate = true;
	bWantsInitializeComponent = true;
}

void UAwarnessComponent::InitializeComponent()
{
	AICRef = Cast<AAI_BaseController>(GetOwner());
	
	Super::InitializeComponent();
}

void UAwarnessComponent::UpdateAwarnessValue(float AwarnesssDelta)
{
	if (IsValid(AICRef) && GetCanUpdateAwarness())
	{
		if (AwarnesssDelta > 0)
		{
			
		}
		
		CurrentAwarnessValue = FMath::Clamp(CurrentAwarnessValue + AwarnesssDelta, 0.f, MaxAwarnessValue);
		
		if (CurrentAwarnessValue >= MaxAwarnessValue)
		{
			CurrentAwarnessValue = MaxAwarnessValue;
			
			SetCanUpdateAwarness(false);
			//Activate Alert
		}
	}
}


// Called when the game starts
void UAwarnessComponent::BeginPlay()
{
	Super::BeginPlay();

}

