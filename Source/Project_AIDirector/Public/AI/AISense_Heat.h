// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AISense.h"
#include "AISense_Heat.generated.h"

class UAISenseConfig_Heat;

USTRUCT()
struct FAIHeatEvent
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TObjectPtr<AActor> Instigator;
	
	UPROPERTY()
	TObjectPtr<AActor> Target;
	
	UPROPERTY()
	FVector Location = FVector::ZeroVector;
	
	UPROPERTY()
	float Strenght = 0.f;
	
	//Check if stimulus is perceived or lost
	UPROPERTY()
	bool IsSuccessfullyHeatingUp = true;
	
	FGenericTeamId TeamIdentifier = FGenericTeamId::NoTeam;
	
	FAIHeatEvent() = default;
	
	FAIHeatEvent(AActor* InHeatInstigator, AActor* InTarget, const FVector& HeatLocation, const float InStrenght, const bool InIsSuccessfullyHeatingUp)
		: Instigator(InHeatInstigator), Target(InTarget), Location(HeatLocation), Strenght(InStrenght), IsSuccessfullyHeatingUp(InIsSuccessfullyHeatingUp)
	{
		TeamIdentifier = FGenericTeamId::GetTeamIdentifier(InHeatInstigator);
	}
	
	//Link the event to sense
	typedef class UAISense_Heat FSenseClass;
};


UCLASS()
class PROJECT_AIDIRECTOR_API UAISense_Heat : public UAISense
{
	GENERATED_BODY()
	
public:
	
	struct FDigestedHeatProperties
	{
		//float HeatRadius;
		bool bDisplaySuccessDebug;
		FColor SuccessDebugColor;
		bool bDisplayFailDebug;
		FColor FailDebugColor;
		
		FDigestedHeatProperties();
		FDigestedHeatProperties(const UAISenseConfig_Heat& SenseConfig);
	};
	
	TMap<FPerceptionListenerID, FDigestedHeatProperties> DigestedProperties;
	
	UAISense_Heat(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION(BlueprintCallable, Category = "AI|Perception", meta = (WorldContext = "WorldContextObject"))
	static void ReportHeatEvent(UObject* WorldContextObject, AActor* Instigator, AActor* Target, FVector Location, float Strenght, bool IsSuccessfullyHeatingUp);
	
	void RegisterEvent(const FAIHeatEvent& Event);
	
	typedef FAIHeatEvent FEventType;
	
protected:
	
	virtual float Update() override;
	
	void EvaluateEvent(const FAIHeatEvent& Event);

	//A listener is someone who has a Perception Component with various senses
	//This funciton will be called when a new listener gained this sense
	void OnNewListenerImpl(const FPerceptionListener& NewListener);

	//Called whenever the listener is removed (eg destroyed or game has stopped)
	void OnListenerRemovedImpl(const FPerceptionListener& RemovedListener);
	
private:
	
	TArray<FAIHeatEvent> HeatEvents;
};
