// Fill out your copyright notice in the Description page of Project Settings.


#include "Project_AIDirector/Public/AI/AI_BaseController.h"
#include "Project_AIDirector/Public/AI/AI_BaseNPC.h"
#include "AIInfo_DataAsset.h" 

#include "Navigation/CrowdFollowingComponent.h"
//#include "Navigation/CrowdFollowingComponent.h"
#include "BrainComponent.h"
#include "GameplayTagsManager.h"
#include "Components/AlertComponent.h"
#include "Components/AwarenessComponent.h"
#include "Enum/Perception/Sight/Enum_SightConeZones.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISense_Touch.h"
#include "Perception/AISenseConfig_Touch.h"
#include "Kismet/KismetMathLibrary.h"
#include "Struct/Perception/Sight/SightConeResult.h"


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
	
	
	//Creation of Awareness and Alert Components
	AwarenessComponent = CreateDefaultSubobject<UAwarenessComponent>(TEXT("Awareness Component"));
	AlertComponent = CreateDefaultSubobject<UAlertComponent>(TEXT("Alert Component"));
}



void AAI_BaseController::OnPossess(APawn* InPawn)
{
	NPCRef = Cast<AAI_BaseNPC>(InPawn);
	
	SetupSightInfo();
	SetupHearingInfo();
	GetAwarenessComponent()->SetupAwareness();
	GetAlertComponent()->SetupAlert();
	
	UpdateCurrentStatusTag(E_AITag::UNAWARE);
	
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

void AAI_BaseController::UpdateCurrentStatusTag(E_AITag NewTag)
{
	switch (NewTag)
	{
		case E_AITag::UNAWARE:
			{
				CurrentStatusTag = UGameplayTagsManager::Get().RequestGameplayTag(TEXT("AIStatus.Unaware"));
				break;
			}
		case E_AITag::SUSPICIOUS:
			{
				CurrentStatusTag = UGameplayTagsManager::Get().RequestGameplayTag(TEXT("AIStatus.Suspicious"));
				break;
			}
		case E_AITag::HUNTING:
			{
				CurrentStatusTag = UGameplayTagsManager::Get().RequestGameplayTag(TEXT("AIStatus.Hunting"));
				break;
			}
		case E_AITag::ALERTED:
			{
				CurrentStatusTag = UGameplayTagsManager::Get().RequestGameplayTag(TEXT("AIStatus.Alerted"));
				break;
			}
	}
}

bool AAI_BaseController::CheckCurrentStatusTag(E_AITag TagToCheck)
{
	switch (TagToCheck)
	{
	case E_AITag::UNAWARE:
		{
			return GetCurrentStatusTag().MatchesTagExact(UGameplayTagsManager::Get().RequestGameplayTag(TEXT("AIStatus.Unaware")));
		}
	case E_AITag::SUSPICIOUS:
		{
			return GetCurrentStatusTag().MatchesTagExact(UGameplayTagsManager::Get().RequestGameplayTag(TEXT("AIStatus.Suspicious")));
		}
	case E_AITag::HUNTING:
		{
			return GetCurrentStatusTag().MatchesTagExact(UGameplayTagsManager::Get().RequestGameplayTag(TEXT("AIStatus.Hunting")));
		}
	case E_AITag::ALERTED:
		{
			return GetCurrentStatusTag().MatchesTagExact(UGameplayTagsManager::Get().RequestGameplayTag(TEXT("AIStatus.Alerted")));
		}
	}
	
	return false;
}

void AAI_BaseController::OnLoseSightTimerFinished()
{
	if (HasLoseSight)
	{
		if (CheckCurrentStatusTag(E_AITag::ALERTED))
		{
			UpdateCurrentStatusTag(E_AITag::HUNTING);
		}
	}
	
	ClearLoseSight();
}

void AAI_BaseController::ClearLoseSight()
{
	HasLoseSight = false;
	GetWorld()->GetTimerManager().ClearTimer(LoseSightTimerHandle);
}

FSightConeResult AAI_BaseController::GetTypeOfSightCone(AActor* UpdatedActor)
{
	FSightConeResult Result;
	
	if (IsValid(UpdatedActor) && GetNPCRef())
	{
		//float CurrentDistance = (GetNPCRef()->GetActorLocation() - UpdatedActor->GetActorLocation()).Length();
		Result.PlayerDistance = (GetNPCRef()->GetActorLocation() - UpdatedActor->GetActorLocation()).Length();
		
		float DotProduct = FVector::DotProduct(GetNPCRef()->GetActorForwardVector(), (UpdatedActor->GetActorLocation() - GetNPCRef()->GetActorLocation()).GetSafeNormal());
		//DegAcos change from radiant (default returned value) to degrees
		float AngleTowardsTarget = UKismetMathLibrary::DegAcos(DotProduct);
		
		if (DotProduct > 0)
		{
			if (AngleTowardsTarget <= GetNPCRef()->GetAIInfo_DataAsset()->SightPeripheralHalfAngleDegree_Narrow)
			{
				Result.ConeZone = E_SightConeZones::NARROW;
			}
			else if (AngleTowardsTarget <= GetNPCRef()->GetAIInfo_DataAsset()->SightPeripheralHalfAngleDegree_Wide &&
					 Result.PlayerDistance <= GetNPCRef()->GetAIInfo_DataAsset()->SightRadius_Wide)
			{
				Result.ConeZone = E_SightConeZones::WIDE;
			}
			else if (AngleTowardsTarget <= GetNPCRef()->GetAIInfo_DataAsset()->SightPeripheralHalfAngleDegree_Peripheral &&
					 Result.PlayerDistance <= GetNPCRef()->GetAIInfo_DataAsset()->SightRadius_Peripheral)
			{
				Result.ConeZone = E_SightConeZones::PERIPHERAL;
			}
		}
		else
		{
			if (Result.PlayerDistance <= GetNPCRef()->GetAIInfo_DataAsset()->SightRadius_Backward)
			{
				Result.ConeZone = E_SightConeZones::BACKWARD;
			}
		}
	}
	
	return Result;
}

void AAI_BaseController::ActorPerceivedUpdate_Implementation(AActor* UpdatedActor, FAIStimulus Stimulus)
{
	if (!BrainComponent || !BrainComponent->IsRunning() || !IsValid(UpdatedActor))
	{
		return;
	}
	
	E_AISense CurrentSenseUsed = E_AISense::NONE;
	
	if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
	{
		CurrentSenseUsed = E_AISense::SIGHT;
		E_SightConeZones CurrentTypeOfCone = E_SightConeZones::NONE;
		
		if (Stimulus.WasSuccessfullySensed())
		{
			//Get Player Distance and Cone already Calculated
			FSightConeResult SightResult = GetTypeOfSightCone(UpdatedActor);
			CurrentTypeOfCone = SightResult.ConeZone;
			
			if (CurrentTypeOfCone != E_SightConeZones::NOTSEEN)
			{
				//Initial Neutral Value
				float DistanceMultiplier = 1.0;
				
				if (GetNPCRef() && GetNPCRef()->GetAIInfo_DataAsset())
				{
					const UAIInfo_DataAsset* Data = GetNPCRef()->GetAIInfo_DataAsset();
                
					//Maximum radius based on the cone to scale the proportion
					float MaxConeRange = Data->SightRadius;
					switch (CurrentTypeOfCone)
					{
					case E_SightConeZones::NARROW:       MaxConeRange = Data->SightRadius; break;
					case E_SightConeZones::WIDE:         MaxConeRange = Data->SightRadius_Wide; break;
					case E_SightConeZones::PERIPHERAL:   MaxConeRange = Data->SightRadius_Peripheral; break;
					case E_SightConeZones::BACKWARD:     MaxConeRange = Data->SightRadius_Backward; break;
					default: break;
					}
                
					//Dynamic multiplier calculation based on distances and data asset parameters
					DistanceMultiplier = FMath::GetMappedRangeValueClamped(
						FVector2D(0.0f, MaxConeRange),
						FVector2D(Data->SightMultiplier_Max, Data->SightMultiplier_Min),
						SightResult.PlayerDistance
					);
					//DEBUG
					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Sight Distance Multiplier: %f"), DistanceMultiplier));
					}
				}
				
				GetAwarenessComponent()->UpdateAwarenessValueFromSense(CurrentSenseUsed, false, CurrentTypeOfCone, DistanceMultiplier);
				GetAlertComponent()->UpdateAlertValueFromSense(CurrentSenseUsed, CurrentTypeOfCone, DistanceMultiplier);
			
				if (CheckCurrentStatusTag(E_AITag::HUNTING))
				{
					UpdateCurrentStatusTag(E_AITag::ALERTED);
				}
			
				ClearLoseSight();
			}
			
		}
		if (CurrentTypeOfCone == E_SightConeZones::NONE || CurrentTypeOfCone == E_SightConeZones::NOTSEEN)
		{
			if (!HasLoseSight)
			{
				HasLoseSight = true;
				GetWorld()->GetTimerManager().SetTimer(LoseSightTimerHandle, this, &AAI_BaseController::OnLoseSightTimerFinished, GetNPCRef()->GetAIInfo_DataAsset()->LoseSightTimer,false);
			}
		}
		
	}
	else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
	{
		CurrentSenseUsed = E_AISense::HEARING;
		
		if (Stimulus.WasSuccessfullySensed())
		{
			//Calculate Noise Distance
			float SoundDistance = (GetNPCRef()->GetActorLocation() - Stimulus.StimulusLocation).Size();
			float MaxHearingRange = GetNPCRef()->GetAIInfo_DataAsset()->RunHearingRange; //Default RUN Range
          
			if (Stimulus.Tag == "Walk")
			{
				MaxHearingRange = GetNPCRef()->GetAIInfo_DataAsset()->WalkHearingRange;
			}
			
			
			if (Stimulus.Tag == "Run" ||
					Stimulus.Tag == "Whistle" ||
						Stimulus.Tag == "Walk" &&
						(GetNPCRef()->GetActorLocation() - Stimulus.StimulusLocation).Size() <= GetNPCRef()->GetAIInfo_DataAsset()->WalkHearingRange)
			{
				float HearingMultiplier = 1.0f;
             
				if (GetNPCRef() && GetNPCRef()->GetAIInfo_DataAsset())
				{
					const UAIInfo_DataAsset* Data = GetNPCRef()->GetAIInfo_DataAsset();
					
					//Map the distances
					HearingMultiplier = FMath::GetMappedRangeValueClamped(
				   FVector2D(0.0f, MaxHearingRange),
				   FVector2D(Data->HearingMultiplier_Max, Data->HearingMultiplier_Min),
					SoundDistance
				);
					
					//DEBUG
					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Sound Distance: %f"), SoundDistance));
					}
				}
             
				//Pass the hearing multiplier
				GetAwarenessComponent()->UpdateAwarenessValueFromSense(
				   CurrentSenseUsed, 
				   (Stimulus.Tag == "Whistle" ? true : false), 
				   E_SightConeZones::NONE, 
				   HearingMultiplier
				);
				
				//DEBUG
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Hearing Multiplier: %f"), HearingMultiplier));
				}
			}
		}
		
	}
	else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Touch>())
	{
		CurrentSenseUsed = E_AISense::TOUCH;
		
		if (Stimulus.WasSuccessfullySensed())
		{
			GetAwarenessComponent()->UpdateAwarenessValueFromSense(CurrentSenseUsed);
			GetAlertComponent()->UpdateAlertValueFromSense(CurrentSenseUsed);
		}
	}
}

