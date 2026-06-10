// Fill out your copyright notice in the Description page of Project Settings.


#include "Project_AIDirector/Public/AI/AI_BaseController.h"
#include "Project_AIDirector/Public/AI/AI_BaseNPC.h"
#include "AIInfo_DataAsset.h" 

#include "Navigation/CrowdFollowingComponent.h"
//#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISense_Touch.h"
#include "Perception/AISenseConfig_Touch.h"


AAI_BaseController::AAI_BaseController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UPathFollowingComponent>(TEXT("PathFollowingComponent")))
{
	//Setup AI Path Following Quality if using Crowd
	
	if (UCrowdFollowingComponent* CrowdComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		CrowdComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
	}
	
	SetGenericTeamId(FGenericTeamId(1));
	
	//Setup AI Perception
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));
}



void AAI_BaseController::OnPossess(APawn* InPawn)
{
	NPCRef = Cast<AAI_BaseNPC>(InPawn);
	
	SetupSightInfo();
	SetupHearingInfo();
	
	Super::OnPossess(InPawn);
	
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAI_BaseController::ActorPerceivedUpdate);
}

ETeamAttitude::Type AAI_BaseController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const APawn* OtherPawn = Cast<APawn>(&Other))
	{
		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			FGenericTeamId OtherTeamID = TeamAgent->GetGenericTeamId();
			if (OtherTeamID == 255)
			{
				return ETeamAttitude::Neutral;
			}
			else if (OtherTeamID == GetGenericTeamId())
			{
				return ETeamAttitude::Friendly;
			}
			else
			{
				{
					return ETeamAttitude::Hostile;
				}
			}
		}
	}
	
	return ETeamAttitude::Hostile;
}

void AAI_BaseController::SetupSightInfo()
{
	if (this == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Controller == nullptr"));
		return;
	}
	
	FAISenseID Id = UAISense::GetSenseID(UAISense_Sight::StaticClass());
	if (!Id.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Wrong Sense ID"));
		return;
	}
	
	auto Perception = GetAIPerceptionComponent();
	if (Perception == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Perception == nullptr"));
		return;
	}
	
	auto Config = Perception->GetSenseConfig(Id);
	if (Config == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Config == nullptr"));
		return;
	}
	
	auto ConfigSight = Cast<UAISenseConfig_Sight>(Config);
	
	ConfigSight->SightRadius = GetNPCRef()->GetAIInfo_DataAsset()->SightRadius;
	ConfigSight->LoseSightRadius = GetNPCRef()->GetAIInfo_DataAsset()->LoseSightRadius;
	ConfigSight->PeripheralVisionAngleDegrees = GetNPCRef()->GetAIInfo_DataAsset()->PeripheralVisionAngleDegrees;
	
	Perception->RequestStimuliListenerUpdate();
}

void AAI_BaseController::SetupHearingInfo()
{
	if (this == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Controller == nullptr"));
		return;
	}
	
	FAISenseID Id = UAISense::GetSenseID(UAISense_Hearing::StaticClass());
	if (!Id.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Wrong Sense ID"));
		return;
	}
	
	auto Perception = GetAIPerceptionComponent();
	if (Perception == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Perception == nullptr"));
		return;
	}
	
	auto Config = Perception->GetSenseConfig(Id);
	if (Config == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Config == nullptr"));
		return;
	}
	
	auto ConfigHearing = Cast<UAISenseConfig_Hearing>(Config);
	
	ConfigHearing->HearingRange = GetNPCRef()->GetAIInfo_DataAsset()->RunHearingRange;
	
	
	Perception->RequestStimuliListenerUpdate();
	
}

void AAI_BaseController::ActorPerceivedUpdate_Implementation(AActor* UpdatedActor, FAIStimulus Stimulus)
{
	
}
