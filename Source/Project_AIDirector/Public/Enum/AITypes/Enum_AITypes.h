#pragma once

//Enum AI Types
UENUM(BlueprintType)
enum class E_AITypes : uint8
{
	REGULAR		UMETA(DisplayName = "Regular"),
	ELITE		UMETA(DisplayName = "Elite")
};


//Enum Status
UENUM(BlueprintType)
enum class E_AITag : uint8
{
	UNAWARE			UMETA(DisplayName = "Unaware"),
	SUSPICIOUS		UMETA(DisplayName = "Suspicious"),
	HUNTING			UMETA(DisplayName = "Hunting"),
	ALERTED			UMETA(DisplayName = "Alerted")
};