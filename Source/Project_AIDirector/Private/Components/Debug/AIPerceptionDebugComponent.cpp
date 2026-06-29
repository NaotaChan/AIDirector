// Fill out your copyright notice in the Description page of Project Settings.
//component maade with the help of AI

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

static void DrawDebug2DSector(const UWorld* World, const FVector& Center, const FVector& Direction, float Radius, float HalfAngleDegrees, const FColor& Color, float HeightOffset = 5.f)
{
	FVector DrawCenter = Center + FVector(0.f, 0.f, HeightOffset);
    
	//Segments
	int32 Segments = FMath::Max(10, FMath::CeilToInt(HalfAngleDegrees / 2.0f)); 
    
	FVector Forward = Direction.GetSafeNormal2D();
	FRotator Rot = Forward.Rotation();

	float StartAngle = Rot.Yaw - HalfAngleDegrees;
	float AngleStep = (HalfAngleDegrees * 2.0f) / Segments;

	//Calculate the first point of the arc
	FVector PrevPoint = DrawCenter + FRotator(0, StartAngle, 0).Vector() * Radius;
    
	//Left side of the cone
	DrawDebugLine(World, DrawCenter, PrevPoint, Color, false, -1.f, 0, 2.f);

	//Draw the arc
	for (int32 i = 1; i <= Segments; ++i)
	{
		FVector NextPoint = DrawCenter + FRotator(0, StartAngle + (i * AngleStep), 0).Vector() * Radius;
		DrawDebugLine(World, PrevPoint, NextPoint, Color, false, -1.f, 0, 2.f);
		PrevPoint = NextPoint;
	}

	//Right side of the cone
	DrawDebugLine(World, PrevPoint, DrawCenter, Color, false, -1.f, 0, 2.f);
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
	
	//Debug Circle
	//Vert offset to lift the hoop off the ground
	FVector DrawLoc = Location + FVector(0.f, 0.f, 5.f);
	
	//Vectors defining the horizontal plane for DrawDebugCircle
	FVector YAxis = FVector::RightVector;
	FVector ZAxis = FVector::ForwardVector;
	
	//HEARING
	if (bDrawHearing && bIsDeaf == false)
	{
		DrawDebugCircle(
			World,
			DrawLoc,
			Data->WalkHearingRange, //HEARING WAL RANGE
			32,
			FColor::Red, 
			false, 
			-1.f, 
			0, 
			2.f, 
			YAxis, 
			ZAxis, 
			false
		);
		
		DrawDebugCircle(
			World,
			DrawLoc,
			Data->RunHearingRange, //HEARING RUN RANGE
			32,
			FColor::Yellow, 
			false, 
			-1.f, 
			0, 
			2.f, 
			YAxis, 
			ZAxis, 
			false
		);
	}

	//SIGHT
	if (bDrawSight && bIsBlind == false)
	{
		FVector Forward = Rotation.Vector();

		// NARROW
		DrawDebug2DSector(World, Location, Forward, Data->SightRadius, Data->SightPeripheralHalfAngleDegree_Narrow, FColor::Red);

		// WIDE
		DrawDebug2DSector(World, Location, Forward, Data->SightRadius_Wide, Data->SightPeripheralHalfAngleDegree_Wide, FColor::Blue);

		// PERIPHERAL
		DrawDebug2DSector(World, Location, Forward, Data->SightRadius_Peripheral, Data->SightPeripheralHalfAngleDegree_Peripheral, FColor::Purple);

		// BACKWARD
		DrawDebugCircle(World, DrawLoc, Data->SightRadius_Backward, 32, FColor::Green, false, -1.f, 0, 2.f, YAxis, ZAxis, false);
	}
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


