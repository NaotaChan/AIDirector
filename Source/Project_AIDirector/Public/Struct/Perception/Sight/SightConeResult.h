// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enum/Perception/Sight/Enum_SightConeZones.h"
#include "SightConeResult.generated.h"

USTRUCT(BlueprintType)
struct FSightConeResult
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadOnly, Category = "AI Perception | Sight")
	E_SightConeZones ConeZone = E_SightConeZones::NOTSEEN;

	UPROPERTY(BlueprintReadOnly, Category = "AI Perception | Sight")
	float PlayerDistance = 0.0f;
};
