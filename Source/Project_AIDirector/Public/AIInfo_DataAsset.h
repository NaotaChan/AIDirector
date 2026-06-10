// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AIInfo_DataAsset.generated.h"

UCLASS()
class PROJECT_AIDIRECTOR_API UAIInfo_DataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
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
	float PeripheralVisionAngleDegrees = 100.f;
	
	
	//hearing
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perception | Hearing")
	float RunHearingRange = 750.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perception | Hearing")
	float WalkHearingRange = 250.f;
};
