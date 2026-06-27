// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Debug/AIPerceptionDebugComponent.h"
#include "AIInfo_DataAsset.h"
#include "DrawDebugHelpers.h"
#include "Perception/AIPerceptionComponent.h"
#include "AI/AI_BaseController.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"


UAIPerceptionDebugComponent::UAIPerceptionDebugComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UAIPerceptionDebugComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UAIPerceptionDebugComponent::DrawDebug(
	const UAIInfo_DataAsset* Data,
	const FVector& Location,
	const FRotator& Rotation)
{
	if (!bEnableDebug || !Data)
		return;

	UWorld* World = GetWorld();
	if (!World)
		return;
	
	//HEARING
	if (bDrawHearing)
	{
		DrawDebugCylinder(
			World,
			Location,
			Location + FVector(0.f, 0.f, 5.f),
			Data->WalkHearingRange,
			32,
			FColor::Yellow,
			false,
			-1.f,
			0,
			2.f
		);

		DrawDebugCylinder(
			World,
			Location,
			Location + FVector(0.f, 0.f, 5.f),
			Data->RunHearingRange,
			32,
			FColor::Red,
			false,
			-1.f,
			0,
			2.f
		);
	}

	//TODO: SIGHT
	
}

void UAIPerceptionDebugComponent::SetIsBlind()
{
	if (!bIsBlind) return; 
	if (!ControllerRef) return;

	UAIPerceptionComponent* Perception = ControllerRef->GetAIPerceptionComponent();
	if (!Perception) return;

	FAISenseID Id = UAISense::GetSenseID(UAISense_Sight::StaticClass());
	UAISenseConfig_Sight* ConfigSight = Cast<UAISenseConfig_Sight>(Perception->GetSenseConfig(Id));
	if (!ConfigSight) return;

	ConfigSight->SightRadius = 0.f;
	ConfigSight->LoseSightRadius = 0.f;
	Perception->RequestStimuliListenerUpdate();
}

void UAIPerceptionDebugComponent::SetIsDeaf()
{
	if (!bIsDeaf) return;
	if (!ControllerRef) return;

	UAIPerceptionComponent* Perception = ControllerRef->GetAIPerceptionComponent();
	if (!Perception) return;

	FAISenseID Id = UAISense::GetSenseID(UAISense_Hearing::StaticClass());
	UAISenseConfig_Hearing* ConfigHearing = Cast<UAISenseConfig_Hearing>(Perception->GetSenseConfig(Id));
	if (!ConfigHearing) return;

	ConfigHearing->HearingRange = 0.f;
	Perception->RequestStimuliListenerUpdate();
}



