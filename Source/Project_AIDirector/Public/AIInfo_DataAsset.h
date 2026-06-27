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
	E_AITypes AITypes = E_AITypes::REGULAR; 
	
	
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
	float LoseSightRadius = 700.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perception | Sight")
	float LoseSightTimer = 1.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perception | Sight")
	float PeripheralVisionAngleDegrees = 100.f;
	
	
	//hearing
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perception | Hearing")
	float RunHearingRange = 750.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perception | Hearing")
	float WalkHearingRange = 250.f;
	
	
	
	//Awareness
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Awareness | Setup")
	float MaxAwarenessValue = 100.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Awareness | Setup")
	float AwarenessDecreaseValue = 1.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Awareness | Setup")
	float AwarenessDecreaseTime = 1.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Awareness | Setup")
	float AwarenessPauseTime = 2.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Awareness | Hearing")
	float AwarenessIncreaseOnHearing = 5.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Awareness | Sight")
	float AwarenessIncreaseOnSight = 15.f;
	
	//Alert
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Alert | Setup")
	float MaxAlertValue = 100.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Alert | Setup")
	float AlertDecreaseValue = 1.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Alert | Setup")
	float AlertDecreaseTime = 0.5f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Alert | Setup")
	float AlertPauseTime = 1.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Alert | Sight")
	float AlertIncreaseOnSight = 20.f;

};
