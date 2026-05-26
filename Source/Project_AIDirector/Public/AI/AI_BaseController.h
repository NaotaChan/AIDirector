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
	UFUNCTION(BlueprintPure, Category = "NPC")
	AAI_BaseNPC* GetNPCRef() {return NPCRef;}

protected:
	virtual void OnPossess(APawn* InPawn) override;
	AAI_BaseNPC* NPCRef;

};
