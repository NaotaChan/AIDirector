// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Debug/AIPerceptionDebugComponent.h"
#include "AIInfo_DataAsset.h"
#include "DrawDebugHelpers.h"


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