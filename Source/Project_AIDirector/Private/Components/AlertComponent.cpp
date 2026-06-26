// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AlertComponent.h"
#include "AI/AI_BaseController.h"
#include "AI/AI_BaseNPC.h"
#include "Components/AwarenessComponent.h"
#include "AIInfo_DataAsset.h"



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

void UAlertComponent::SetupAlert()
{
	if (IsValid(AICRef) &&
		IsValid(AICRef->GetNPCRef()) &&
			IsValid(AICRef->GetNPCRef()->GetAIInfo_DataAsset()))
	{
		MaxAlertValue = AICRef->GetNPCRef()->GetAIInfo_DataAsset()->MaxAlertValue;
		AlertDecreaseValue = AICRef->GetNPCRef()->GetAIInfo_DataAsset()->AlertDecreaseValue;
		AlertDecreaseTime = AICRef->GetNPCRef()->GetAIInfo_DataAsset()->AlertDecreaseTime;
		AlertPauseTime = AICRef->GetNPCRef()->GetAIInfo_DataAsset()->AlertPauseTime;
		AlertIncreaseOnSight = AICRef->GetNPCRef()->GetAIInfo_DataAsset()->AlertIncreaseOnSight;
	}
}

void UAlertComponent::UpdateAlertValueFromSense(E_AISense InputSense)
{
	switch (InputSense)
	{
	case E_AISense::SIGHT:
		{
			UpdateAlertValue(AlertIncreaseOnSight);
			break;
		}
	case E_AISense::HEARING:
		{
			break;
		}
	case E_AISense::TOUCH:
		{
			UpdateAlertValue(MaxAlertValue);
			break;
		}
	}
}

void UAlertComponent::UpdateAlertValue(float AlertedDelta)
{
	
}

void UAlertComponent::OnPauseFinished()
{
	GetWorld()->GetTimerManager().ClearTimer(PauseTimerHandle);
	
	if (!GetIsDecreasing())
	{
		SetIsDecreasing(true);
		OnDecreaseAlertValue();
		GetWorld()->GetTimerManager().SetTimer(DecreaseTimerHandle, this, &UAlertComponent::OnDecreaseAlertValue, AlertDecreaseTime, true);
	}	
}

void UAlertComponent::OnDecreaseAlertValue()
{
	if (GetIsDecreasing())
	{
		UpdateAlertValue(-AlertDecreaseValue);
		
		if (CurrentAlertValue <= 0)
		{
			CurrentAlertValue = 0.f;
			SetIsDecreasing(false);
			GetWorld()->GetTimerManager().ClearTimer(DecreaseTimerHandle);
		}
	}
}

void UAlertComponent::StopAlert()
{
	GetWorld()->GetTimerManager().ClearTimer(DecreaseTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(PauseTimerHandle);
	SetCanUpdateAlert(false);
}

void UAlertComponent::ResetAlert(bool ResetAwareness)
{
	CurrentAlertValue = 0.f;
	SetCanUpdateAlert(true);
	
	//TODO: In the future implement an AWARE status
	
	AICRef->UpdateCurrentStatusTag(E_AITag::UNAWARE);
	
	if (ResetAwareness)
	{
		AICRef->GetAwarenessComponent()->ResetAwareness();
	}
}

// Called when the game starts
void UAlertComponent::BeginPlay()
{
	Super::BeginPlay();
}

