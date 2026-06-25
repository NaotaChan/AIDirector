// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AISenseConfig.h"
#include "AISenseConfig_Heat.generated.h"

class UAISense_Heat;

UCLASS(meta = (DisplayName = "AI Heat config"))
class PROJECT_AIDIRECTOR_API UAISenseConfig_Heat : public UAISenseConfig
{
	GENERATED_BODY()
	
public:
	
	UAISenseConfig_Heat(const FObjectInitializer& ObjectInitializer);
	
	//The class reference which contains the logic for this sense config
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sense", NoClear, config)
	TSubclassOf<UAISense_Heat> Implementation;
	
	//The radius around the pawn that we're checking for "water resources"
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sense", config, meta = (UIMin = 0.0, Clampmin = 0.0))
	//float HeatRadius;
	
	//True if you want to display the success line debug
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sense", config)
	bool bDisplaySuccessDebug;
	
	//Not used as UPROPERTY because it is used only to copy the Protected Debug Color variable
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sense", config)
	FColor SuccessDebugColor;
	
	//True if you want to display the fail line debug
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sense", config)
	bool bDisplayFailDebug;
	
	//Not used as UPROPERTY because it is used only to copy the Protected Debug Color variable
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sense", config)
	FColor FailDebugColor;
	
	
	virtual TSubclassOf<UAISense> GetSenseImplementation() const override;
	
};
