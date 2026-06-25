// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AISense_Heat.h"
#include "AI/AISenseConfig_Heat.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionSystem.h"


UAISense_Heat::UAISense_Heat(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)

{
	if (HasAnyFlags(RF_ClassDefaultObject) == false)
	{
		OnNewListenerDelegate.BindUObject(this, &UAISense_Heat::OnNewListenerImpl);
		OnListenerRemovedDelegate.BindUObject(this, &UAISense_Heat::OnListenerRemovedImpl);
	}
}

UAISense_Heat::FDigestedHeatProperties::FDigestedHeatProperties()
{
	
	//Init
	//HeatRadius = 15.f;
	bDisplaySuccessDebug = false;
	SuccessDebugColor =  FColor::Green;
	bDisplayFailDebug = false;
	FailDebugColor =  FColor::Red;
}

UAISense_Heat::FDigestedHeatProperties::FDigestedHeatProperties(const UAISenseConfig_Heat& SenseConfig)
{
	//HeatRadius = SenseConfig.HeatRadius;
	bDisplaySuccessDebug = SenseConfig.bDisplaySuccessDebug;
	SuccessDebugColor =  SenseConfig.SuccessDebugColor;
	bDisplayFailDebug = SenseConfig.bDisplayFailDebug;
	FailDebugColor =  SenseConfig.FailDebugColor;
}

void UAISense_Heat::OnNewListenerImpl(const FPerceptionListener& NewListener)
{
	UAIPerceptionComponent* ListenerPtr = NewListener.Listener.Get();
	check(ListenerPtr);
	const UAISenseConfig_Heat* SenseConfig = Cast<const UAISenseConfig_Heat>(ListenerPtr->GetSenseConfig(GetSenseID()));
	check(SenseConfig);
	const FDigestedHeatProperties PropertyDigest(*SenseConfig);
	DigestedProperties.Add(NewListener.GetListenerID(), PropertyDigest);
	
}

void UAISense_Heat::OnListenerRemovedImpl(const FPerceptionListener& RemovedListener)
{
	DigestedProperties.FindAndRemoveChecked(RemovedListener.GetListenerID());
}

void UAISense_Heat::ReportHeatEvent(UObject* WorldContextObject, AActor* Instigator, AActor* Target, FVector Location,
	float Strenght, bool IsSuccessfullyHeatingUp)
{
	UAIPerceptionSystem* PerceptionSystem = UAIPerceptionSystem::GetCurrent(WorldContextObject);
	if (PerceptionSystem)
	{
		const FAIHeatEvent Event(Instigator, Target, Location, Strenght, IsSuccessfullyHeatingUp);
		PerceptionSystem->OnEvent(Event);
	}
}

void UAISense_Heat::RegisterEvent(const FAIHeatEvent& Event)
{
	HeatEvents.Add(Event);
	
	RequestImmediateUpdate();
}

float UAISense_Heat::Update()
{
	if (!HeatEvents.IsEmpty())
	{
		for (const FAIHeatEvent& Event : HeatEvents)
		{
			EvaluateEvent(Event);
		}
	}
	
	HeatEvents.Reset();
	return SuspendNextUpdate;
	
}

void UAISense_Heat::EvaluateEvent(const FAIHeatEvent& Event)
{
	if (Event.Target != nullptr && Event.Instigator != nullptr)
	{
		AIPerception::FListenerMap& ListenersMap = *GetListeners();
		
		//For each listener who has this sense we're going to perform a sweep to determine nearby Heat actorss
		for (AIPerception::FListenerMap::TIterator ListenerIt(ListenersMap); ListenerIt; ++ListenerIt)
		{
			FPerceptionListener& PerceptionListener = ListenerIt->Value;
			
			if (PerceptionListener == nullptr || PerceptionListener.HasSense(GetSenseID()) == false)
			{
				//skip listeners null ornot interested in this sense
				continue;
			}
			
			const FDigestedHeatProperties* PropDigest = DigestedProperties.Find(PerceptionListener.GetListenerID());
			if (!PropDigest)
				continue;
			
			FVector TargetLocation = Event.Target->GetActorLocation();
			FVector InstigatorLocation = Event.Instigator->GetActorLocation();
			
			float Distance = FVector::Dist(TargetLocation, InstigatorLocation);
			
			//if (Distance <= PropDigest->HeatRadius)
			if (Event.IsSuccessfullyHeatingUp)
			{
				PerceptionListener.RegisterStimulus(Event.Target, FAIStimulus(*this, Event.Strenght, InstigatorLocation, TargetLocation, FAIStimulus::SensingSucceeded, FName("Heat")));
				if (PropDigest->bDisplaySuccessDebug)
				{
					DrawDebugLine(GetWorld(), InstigatorLocation, TargetLocation, PropDigest->SuccessDebugColor, false, 5.f, 0, 5.f);
				}
			}
			else
			{
				PerceptionListener.RegisterStimulus(Event.Target, FAIStimulus(*this, Event.Strenght, InstigatorLocation, TargetLocation, FAIStimulus::SensingFailed, FName("Heat")));
				if (PropDigest->bDisplayFailDebug)
				{
					DrawDebugLine(GetWorld(), InstigatorLocation, TargetLocation, PropDigest->FailDebugColor, false, 5.f, 0, 5.f);
				}
			}
		}
	}
}




