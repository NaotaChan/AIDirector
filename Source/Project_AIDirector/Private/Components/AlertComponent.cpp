// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AlertComponent.h"
#include "AI/AI_BaseController.h"


// Sets default values for this component's properties
UAlertComponent::UAlertComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	bAutoActivate = true;
	bWantsInitializeComponent = true;
}

void UAlertComponent::InitializeComponent()
{
	AICRef = Cast<AAI_BaseController>(GetOwner());
	
	Super::InitializeComponent();
}

void UAlertComponent::UpdateAlertedValue(float AlertedDelta)
{
	
}

// Called when the game starts
void UAlertComponent::BeginPlay()
{
	Super::BeginPlay();
}

