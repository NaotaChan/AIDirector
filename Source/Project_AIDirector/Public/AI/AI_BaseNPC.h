// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AI_BaseNPC.generated.h"

class AAI_BaseController;
class AAIWaypoint;
class UAIInfo_DataAsset;

UCLASS()
class PROJECT_AIDIRECTOR_API AAI_BaseNPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAI_BaseNPC();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintPure, Category = "AIC")
	AAI_BaseController* GetAICRef() {return AICRef;}
	
	UFUNCTION(BlueprintPure, Category = "Waypoint")
	AAIWaypoint* GetStartWaypoint() {return StartWaypoint;}
	
	UFUNCTION(BlueprintPure, Category = "Data Asset")
	UAIInfo_DataAsset* GetAIInfo_DataAsset() {return AIInfo_DataAsset;}
	
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void ChangeSpeedType();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditInstanceOnly, Category = "Waypoint")
	AAIWaypoint* StartWaypoint;
	
	AAI_BaseController* AICRef;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data Asset")
	UAIInfo_DataAsset* AIInfo_DataAsset;

};
