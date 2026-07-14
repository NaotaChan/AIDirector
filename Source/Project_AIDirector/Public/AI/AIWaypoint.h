// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "AIWaypoint.generated.h"

UCLASS()
class PROJECT_AIDIRECTOR_API AAIWaypoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Waypoint")
	AAIWaypoint* GetNextWaypoint() {return NextWaypoint;}
	
	UFUNCTION(BlueprintPure, Category = "Waypoint")
	float GetWaitTime() {return WaitTime;}
	
	UFUNCTION(BlueprintPure, Category = "Waypoint")
	float GetCloseDistance() {return CloseDistance;}

protected:
	UPROPERTY(EditInstanceOnly, Category = "Waypoint", meta = (EditConditionHides, EditCondition = "IsPreventPassage == false"))
	AAIWaypoint* NextWaypoint;
	
	UPROPERTY(EditInstanceOnly, Category = "Waypoint", meta = (EditConditionHides, EditCondition = "IsPreventPassage == false"))
	float WaitTime = 0.f;
	
	UPROPERTY(EditInstanceOnly, Category = "Waypoint", meta = (EditConditionHides, EditCondition = "IsPreventPassage == false"))
	float CloseDistance = 200.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Prevent Passage Point")
	bool IsPreventPassage = false;
};
