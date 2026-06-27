// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIPerceptionDebugComponent.generated.h"

class UAIInfo_DataAsset;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_AIDIRECTOR_API UAIPerceptionDebugComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAIPerceptionDebugComponent();

	void DrawDebug(const UAIInfo_DataAsset* Data, const FVector& Location, const FRotator& Rotation);

protected:
	
	virtual void BeginPlay() override;
	

	UPROPERTY(EditAnywhere, Category="Debug | Perception")
	bool bEnableDebug = false;

	UPROPERTY(EditAnywhere, Category="Debug | Perception")
	bool bDrawHearing = true;

	UPROPERTY(EditAnywhere, Category="Debug | Perception")
	bool bDrawSight = true;
};
