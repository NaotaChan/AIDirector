// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AI_BaseNPC.generated.h"

class AAI_BaseController;

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
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	AAI_BaseController* AICRef;

};
