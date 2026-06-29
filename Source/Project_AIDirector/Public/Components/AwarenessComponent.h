// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enum/Perception/Sight/Enum_SightConeZones.h"
#include "AwarenessComponent.generated.h"

class AAI_BaseController;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_AIDIRECTOR_API UAwarenessComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAwarenessComponent();
	
	virtual void InitializeComponent() override;
	
	void SetupAwareness();
	
	UFUNCTION(BlueprintPure, Category = "Awareness")
	float GetCurrentAwarenessValue() {return CurrentAwarenessValue;}
	
	UFUNCTION(BlueprintPure, Category = "Awareness")
	float GetMaxAwarnessValue() {return MaxAwarenessValue;}
	
	
	UFUNCTION()
	bool GetCanUpdateAwareness() const {return CanUpdateAwareness;}
	
	UFUNCTION()
	void SetCanUpdateAwareness(bool NewStatus) {CanUpdateAwareness = NewStatus;}
	
	UFUNCTION()
	bool GetIsDecreasing() const {return IsDecreasing;}
	
	UFUNCTION()
	void SetIsDecreasing(bool NewStatus) {IsDecreasing = NewStatus;}
	
	UFUNCTION(BlueprintCallable, Category = "Awareness")
	void UpdateAwarenessValueFromSense(E_AISense InputSense, bool IsFromWhistle = false, E_SightConeZones CurrentTypeOfCone = E_SightConeZones::NONE, float DistanceMultiplier = 1.0f);
	
	UFUNCTION(BlueprintCallable, Category = "Awareness")
	void UpdateAwarenessValue(float AwarenessDelta);
	
	void OnPauseFinished();
	
	void OnDecreaseAwarenessValue();
	
	void StopAwareness();
	
	UFUNCTION(BlueprintCallable, Category = "Awareness")
	void ResetAwareness();
	
	float GetCorrectSightAwareness(E_SightConeZones SightConeType);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY()
	AAI_BaseController* AICRef;
	
	FTimerHandle PauseTimerHandle;
	
	FTimerHandle DecreaseTimerHandle;
	
private:
	
	float CurrentAwarenessValue;
	float MaxAwarenessValue;
	float AwarenessDecreaseValue;
	float AwarenessDecreaseTime;
	float AwarenessPauseTime;
	float AwarenessIncreaseOnHearing;
	float AwarenessIncreaseOnSight_Narrow;
	float AwarenessIncreaseOnSight_Wide;	
	float AwarenessIncreaseOnSight_Peripheral;	
	float AwarenessIncreaseOnSight_Backward;	

	
	bool CanUpdateAwareness;
	bool IsDecreasing;
};
