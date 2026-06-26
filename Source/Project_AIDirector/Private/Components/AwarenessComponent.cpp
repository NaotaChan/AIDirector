// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AwarenessComponent.h"
#include "AI/AI_BaseController.h"
#include "Components/AlertComponent.h"
#include "AI/AI_BaseNPC.h"
#include "AIInfo_DataAsset.h"



// Sets default values for this component's properties
UAwarenessComponent::UAwarenessComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	bAutoActivate = true;
	bWantsInitializeComponent = true;
}

void UAwarenessComponent::InitializeComponent()
{
	AICRef = Cast<AAI_BaseController>(GetOwner());
	
	Super::InitializeComponent();
}

void UAwarenessComponent::SetupAwareness()
{
	if (IsValid(AICRef) &&
			IsValid(AICRef->GetNPCRef()) &&
				IsValid(AICRef->GetNPCRef()->GetAIInfo_DataAsset()))
	{
		MaxAwarenessValue = AICRef->GetNPCRef()->GetAIInfo_DataAsset()->MaxAwarenessValue;
		AwarenessDecreaseValue = AICRef->GetNPCRef()->GetAIInfo_DataAsset()->AwarenessDecreaseValue;
		AwarenessDecreaseTime = AICRef->GetNPCRef()->GetAIInfo_DataAsset()->AwarenessDecreaseTime;
		AwarenessPauseTime = AICRef->GetNPCRef()->GetAIInfo_DataAsset()->AwarenessPauseTime;
		AwarenessIncreaseOnHearing = AICRef->GetNPCRef()->GetAIInfo_DataAsset()->AwarenessIncreaseOnHearing;
		AwarenessIncreaseOnSight = AICRef->GetNPCRef()->GetAIInfo_DataAsset()->AwarenessIncreaseOnSight;
	}
}

void UAwarenessComponent::UpdateAwarenessValueFromSense(E_AISense InputSense, bool IsFromWhistle)
{
	switch (InputSense)
	{
	case E_AISense::SIGHT:
		{
			UpdateAwarenessValue(AwarenessIncreaseOnSight);
			break;
		}
	case E_AISense::HEARING:
		{
			UpdateAwarenessValue(IsFromWhistle ? MaxAwarenessValue : AwarenessIncreaseOnHearing);
			break;
		}
	case E_AISense::TOUCH:
		{
			UpdateAwarenessValue(MaxAwarenessValue);
			break;
		}
	}
}

void UAwarenessComponent::UpdateAwarenessValue(float AwarenessDelta)
{
	if (IsValid(AICRef) && GetCanUpdateAwareness())
	{
		if (AwarenessDelta > 0)
		{
			//Restart the timer if the stimulus persist
			if (PauseTimerHandle.IsValid())
			{
				GetWorld()->GetTimerManager().ClearTimer(PauseTimerHandle);
			}
			
			GetWorld()->GetTimerManager().SetTimer(PauseTimerHandle, this, &UAwarenessComponent::OnPauseFinished, AwarenessPauseTime, false);
			
		}
		
		CurrentAwarenessValue = FMath::Clamp(CurrentAwarenessValue + AwarenessDelta, 0.f, MaxAwarenessValue);
		
		if (CurrentAwarenessValue >= MaxAwarenessValue)
		{
			CurrentAwarenessValue = MaxAwarenessValue;
			
			StopAwareness();
			
			if (IsValid(AICRef->GetAlertComponent()))
			{
				AICRef->GetAlertComponent()->SetCanUpdateAlert(true);
			}
			
			AICRef->UpdateCurrentStatusTag(E_AITag::SUSPICIOUS);
		}
	}
}


void UAwarenessComponent::OnPauseFinished()
{
	GetWorld()->GetTimerManager().ClearTimer(PauseTimerHandle);
	
	if (!GetIsDecreasing())
	{
		SetIsDecreasing(true);
		OnDecreaseAwarenessValue();
		GetWorld()->GetTimerManager().SetTimer(DecreaseTimerHandle, this, &UAwarenessComponent::OnDecreaseAwarenessValue, AwarenessDecreaseTime, true);
	}
}

void UAwarenessComponent::OnDecreaseAwarenessValue()
{
	if (GetIsDecreasing())
	{
		UpdateAwarenessValue(-AwarenessDecreaseValue);
		
		if (CurrentAwarenessValue <= 0)
		{
			CurrentAwarenessValue = 0.f;
			SetIsDecreasing(false);
			GetWorld()->GetTimerManager().ClearTimer(DecreaseTimerHandle);
		}
	}
}

void UAwarenessComponent::StopAwareness()
{
	GetWorld()->GetTimerManager().ClearTimer(DecreaseTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(PauseTimerHandle);
	SetCanUpdateAwareness(false);
}

void UAwarenessComponent::ResetAwareness()
{
	CurrentAwarenessValue = 0.f;
	SetCanUpdateAwareness(true);
	
	//TODO: In the future implement an AWARE status
	
	AICRef->UpdateCurrentStatusTag(E_AITag::UNAWARE);
}

// Called when the game starts
void UAwarenessComponent::BeginPlay()
{
	Super::BeginPlay();

}



