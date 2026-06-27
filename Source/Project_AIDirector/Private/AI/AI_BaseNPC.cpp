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
	
	//Creation of Perception Debug Component
	PerceptionDebugComponent = CreateDefaultSubobject<UAIPerceptionDebugComponent>(TEXT("Perception Debug Component"));
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
	
	if (PerceptionDebugComponent && AICRef)
	{
		PerceptionDebugComponent->SetControllerRef(AICRef);
		PerceptionDebugComponent->SetIsBlind();
		PerceptionDebugComponent->SetIsDeaf();
	}
}

// Called every frame
void AAI_BaseNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
		
	// Perception Debug
	if (IsValid(GetPerceptionDebugComponent()))
	{
		GetPerceptionDebugComponent()->DrawDebug(
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