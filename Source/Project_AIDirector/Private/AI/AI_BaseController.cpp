// Fill out your copyright notice in the Description page of Project Settings.


#include "Project_AIDirector/Public/AI/AI_BaseController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Project_AIDirector/Public/AI/AI_BaseNPC.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"

AAI_BaseController::AAI_BaseController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UPathFollowingComponent>(TEXT("PathFollowingComponent")))
{
	//Setup AI Path Following Quality if using Crowd
	
	if (UCrowdFollowingComponent* CrowdComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		CrowdComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
	}
	
	//Setup AI Perception
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));
}

void AAI_BaseController::OnPossess(APawn* InPawn)
{
	NPCRef = Cast<AAI_BaseNPC>(InPawn);
	
	Super::OnPossess(InPawn);
	
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAI_BaseController::ActorPerceivedUpdate);
}

void AAI_BaseController::ActorPerceivedUpdate_Implementation(AActor* UpdatedActor, FAIStimulus Stimulus)
{
	
}
