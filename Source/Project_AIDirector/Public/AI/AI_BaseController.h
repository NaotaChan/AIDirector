// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI_BaseController.generated.h"

class AAI_BaseNPC;

UCLASS()
class PROJECT_AIDIRECTOR_API AAI_BaseController : public AAIController
{
	GENERATED_BODY()

public:	
	
	AAI_BaseController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	UFUNCTION(BlueprintPure, Category = "NPC")
	AAI_BaseNPC* GetNPCRef() {return NPCRef;}
	
	UFUNCTION(BlueprintNativeEvent)
	void ActorPerceivedUpdate(AActor* UpdatedActor, FAIStimulus Stimulus);
	
	//Team ID
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	
	UFUNCTION()
	void SetupSightInfo();
	
	UFUNCTION()
	void SetupHearingInfo();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	AAI_BaseNPC* NPCRef;

};
