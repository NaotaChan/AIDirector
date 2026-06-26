// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AwarenessComponent.h"
#include "AI/AI_BaseController.h"
#include "Components/AlertComponent.h"



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
			
			SetCanUpdateAwareness(false);
			
			if (IsValid(AICRef->GetAlertComponent()))
			{
				AICRef->GetAlertComponent()->SetCanUpdateAlerted(true);
				AICRef->UpdateCurrentStatusTag(E_AITag::SUSPICIOUS);
			}
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
			CurrentAwarenessValue = 0;
			SetIsDecreasing(false);
			GetWorld()->GetTimerManager().ClearTimer(DecreaseTimerHandle);
		}
	}
}

// Called when the game starts
void UAwarenessComponent::BeginPlay()
{
	Super::BeginPlay();

}



