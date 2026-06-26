// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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
	
	UFUNCTION()
	bool GetCanUpdateAlert() const {return CanUpdateAlert;}
	
	UFUNCTION()
	void SetCanUpdateAlert(bool NewStatus) {CanUpdateAlert = NewStatus;}
	
	UFUNCTION(BlueprintCallable, Category = "Alert")
	void UpdateAlertValueFromSense(E_AISense InputSense);
	
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
	float AlertIncreaseOnSight;	
	
	bool CanUpdateAlert;
	bool IsDecreasing;
};
