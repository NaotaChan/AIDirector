// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameplayTagContainer.h"
#include "Enum/AITypes/Enum_AITypes.h"

#include "AI_BaseController.generated.h"

class UAwarenessComponent;
class UAlertComponent;

UCLASS()
class PROJECT_AIDIRECTOR_API AAI_BaseController : public AAIController
{
	GENERATED_BODY()

public:	
	
	AAI_BaseController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	UFUNCTION(BlueprintPure, Category = "NPC")
	AAI_BaseNPC* GetNPCRef() const {return NPCRef;}
	
	UFUNCTION(BlueprintPure, Category = "Awarness")
	UAwarenessComponent* GetAwarenessComponent() const {return AwarenessComponent;}
	
	UFUNCTION(BlueprintPure, Category = "Alert")
	UAlertComponent* GetAlertComponent() const {return AlertComponent;}
	
	UFUNCTION(BlueprintNativeEvent)
	void ActorPerceivedUpdate(AActor* UpdatedActor, FAIStimulus Stimulus);
	
	//Team ID
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	
	UFUNCTION()
	void SetupSightInfo();
	
	UFUNCTION()
	void SetupHearingInfo();
	
	UFUNCTION(BlueprintPure, Category = "AI Status")
	FGameplayTag GetCurrentStatusTag() const {return CurrentStatusTag;}
	
	UFUNCTION(BlueprintCallable, Category= "AI Status")
	void UpdateCurrentStatusTag(E_AITag NewTag);
	
	UFUNCTION(BlueprintCallable, Category= "AI Status")
	bool CheckCurrentStatusTag(E_AITag TagToCheck);
	

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
	AAI_BaseNPC* NPCRef;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UAwarenessComponent* AwarenessComponent;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UAlertComponent* AlertComponent;
	
	FGameplayTag CurrentStatusTag;

};
