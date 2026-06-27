// Fill out your copyright notice in the Description page of Project Settings.


#include "Project_AIDirector/Public/AI/AI_BaseNPC.h"
#include "Project_AIDirector/Public/AI/AI_BaseController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIInfo_DataAsset.h"
#include "Components/Debug/AIPerceptionDebugComponent.h"


// Sets default values
AAI_BaseNPC::AAI_BaseNPC()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void AAI_BaseNPC::BeginPlay()
{	
	AICRef = Cast<AAI_BaseController>(GetController());
	Super::BeginPlay();
	
	if(GetAIInfo_DataAsset())
	{
		AITypes = GetAIInfo_DataAsset()->AITypes;
	}
	
}

// Called every frame
void AAI_BaseNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
		
	// Perception Debug
	if (AICRef && AICRef->GetPerceptionDebugComponent())
	{
		AICRef->GetPerceptionDebugComponent()->DrawDebug(
			AIInfo_DataAsset,
			GetActorLocation(),
			GetActorRotation()
		);
	}
}

// Called to bind functionality to input
void AAI_BaseNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAI_BaseNPC::ChangeSpeedType(E_AISpeedType NewSpeed)
{
	if (CurrentSpeedType != NewSpeed)
	{
		switch (NewSpeed)
		{
			case E_AISpeedType::WALK:
				{
					CurrentSpeedType = E_AISpeedType::WALK;
					GetCharacterMovement()->MaxWalkSpeed = GetAIInfo_DataAsset()->WalkSpeed;
					break;
				}
			case E_AISpeedType::RUN:
				{
					CurrentSpeedType = E_AISpeedType::RUN;
					GetCharacterMovement()->MaxWalkSpeed = GetAIInfo_DataAsset()->RunSpeed;
					break;
				}		
		}
	}
}


void AAI_BaseNPC::DrawDebugSenses() const
{
	if (!bShowSenseDebug)
		return;

	if (!AIInfo_DataAsset)
		return;

	FVector Location = GetActorLocation();

	if (bShowRunHearingDebug)
	{
		DrawDebugSphere(
			GetWorld(),
			Location,
			AIInfo_DataAsset->RunHearingRange,
			32,
			FColor::Yellow,
			false,
			-1.f,
			0,
			2.f
		);
	}

	if (bShowWalkHearingDebug)
	{
		DrawDebugSphere(
			GetWorld(),
			Location,
			AIInfo_DataAsset->WalkHearingRange,
			32,
			FColor::Red,
			false,
			-1.f,
			0,
			2.f
		);
	}

	//TODO: Sight Draw Debug
}