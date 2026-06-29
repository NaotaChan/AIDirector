// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enum/Perception/Sight/Enum_SightConeZones.h"
#include "AlertComponent.generated.h"

class AAI_BaseController;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_AIDIRECTOR_API UAlertComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAlertComponent();
		
	virtual void InitializeComponent() override;
	
	void SetupAlert();
	
	
	UFUNCTION(BlueprintPure, Category = "Alert")
	float GetCurrentAlertValue() {return CurrentAlertValue;}
	
	UFUNCTION(BlueprintPure, Category = "Alert")
	float GetMaxAlertValue() {return MaxAlertValue;}
	
	UFUNCTION()
	bool GetCanUpdateAlert() const {return CanUpdateAlert;}
	
	UFUNCTION()
	void SetCanUpdateAlert(bool NewStatus) {CanUpdateAlert = NewStatus;}
	
	UFUNCTION(BlueprintCallable, Category = "Alert")
	void UpdateAlertValueFromSense(E_AISense InputSense, E_SightConeZones CurrentTypeOfCone = E_SightConeZones::NONE, float DistanceMultiplier = 1.0f);
	
	UFUNCTION(BlueprintCallable, Category = "Alert")
	void UpdateAlertValue(float AlertDelta, bool IsFromTouching = false);
	
	UFUNCTION()
	bool GetIsDecreasing() const {return IsDecreasing;}
	
	UFUNCTION()
	void SetIsDecreasing(bool NewStatus) {IsDecreasing = NewStatus;}
	
	void OnPauseFinished();
	
	void OnDecreaseAlertValue();
	
	void StopAlert();
	
	UFUNCTION(BlueprintCallable, Category = "Alert")
	void ResetAlert(bool ResetAwareness = true);
	
	float GetCorrectSightAlert(E_SightConeZones SightConeType);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
		
	UPROPERTY()
	AAI_BaseController* AICRef;
	
	FTimerHandle PauseTimerHandle;
	
	FTimerHandle DecreaseTimerHandle;
	
private:
	
	float CurrentAlertValue;
	float MaxAlertValue;
	float AlertDecreaseValue;
	float AlertDecreaseTime;
	float AlertPauseTime;
	float AlertIncreaseOnSight_Narrow;
	float AlertIncreaseOnSight_Wide;	
	float AlertIncreaseOnSight_Peripheral;	
	float AlertIncreaseOnSight_Backward;	;	
	
	bool CanUpdateAlert;
	bool IsDecreasing;
};
