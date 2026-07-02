// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enum/AITypes/Enum_AITypes.h"
#include "AIInfo_DataAsset.generated.h"

UCLASS()
class PROJECT_AIDIRECTOR_API UAIInfo_DataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	//AI Types
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI Types")
	E_AITypes AITypes = E_AITypes::NONE; 
	
	
	//Movement
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float WalkSpeed = 200.f; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float RunSpeed = 4500.f; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float RotationSpeed = 2.f; 
	
	
	//Perception
	//sight
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perception | Sight")
	float SightRadius = 700.f; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perception | Sight")
	float SightRadius_Wide = 500.f; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perception | Sight")
	float SightRadius_Peripheral = 250.f; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perception | Sight")
	float SightRadius_Backward = 150.f; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perception | Sight")
	float LoseSightRadius = 700.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perception | Sight")
	float LoseSightTimer = 1.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perception | Sight")
	float PeripheralVisionAngleDegrees = 100.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perception | Sight")
	float SightPeripheralHalfAngleDegree_Narrow = 20.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perception | Sight")
	float SightPeripheralHalfAngleDegree_Wide = 55.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perception | Sight")
	float SightPeripheralHalfAngleDegree_Peripheral = 90.f;
	
	
	//Min & Max multiplier of sight
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perception | Sight", meta = (ClampMin = "0.0", ClampMax = "2.0"))
	float SightMultiplier_Max = 1.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perception | Sight", meta = (ClampMin = "0.0", ClampMax = ".0"))
	float SightMultiplier_Min = 0.2f;
	
	//Min & Max multiplier of hearing
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perception | Hearing", meta = (ClampMin = "0.0", ClampMax = "2.0"))
	float HearingMultiplier_Max = 1.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perception | Hearing", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float HearingMultiplier_Min = 0.2f;
	
	
	//hearing
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perception | Hearing")
	float RunHearingRange = 750.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perception | Hearing")
	float WalkHearingRange = 250.f;
	
	
	
	//Awareness
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Awareness | Setup")
	float MaxAwarenessValue = 100.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Awareness | Setup")
	float AwarenessDecreaseValue = 5.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Awareness | Setup")
	float AwarenessDecreaseTime = 1.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Awareness | Setup")
	float AwarenessPauseTime = 2.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Awareness | Hearing")
	float AwarenessIncreaseOnHearing = 20.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Awareness | Sight")
	float AwarenessIncreaseOnSight_Narrow = 20.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Awareness | Sight")
	float AwarenessIncreaseOnSight_Wide = 10.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Awareness | Sight")
	float AwarenessIncreaseOnSight_Peripheral = 5.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Awareness | Sight")
	float AwarenessIncreaseOnSight_Backward = 2.f;
	
	//Alert
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Alert | Setup")
	float MaxAlertValue = 100.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Alert | Setup")
	float AlertDecreaseValue = 1.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Alert | Setup")
	float AlertDecreaseTime = 0.5f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Alert | Setup")
	float AlertPauseTime = 0.5f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Alert | Sight")
	float AlertIncreaseOnSight_Narrow = 15.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Alert | Sight")
	float AlertIncreaseOnSight_Wide = 10.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Alert | Sight")
	float AlertIncreaseOnSight_Peripheral = 5.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Alert | Sight")
	float AlertIncreaseOnSight_Backward = 2.f;
	
	//Behavior Tree
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BT | Investigate")
	float InvestigateTimer = 15.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BT | Hunting")
	float HuntingTimer = 30.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BT | Disturbance")
	float DisturbanceCooldownTimer = 1.f;
	

};
