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
	

protected:
	UPROPERTY(EditInstanceOnly, Category = "Waypoint")
	AAIWaypoint* NextWaypoint;
	
	UPROPERTY(EditInstanceOnly, Category = "Waypoint")
	float WaitTime;

};
