#pragma once

//Enum AI Types
UENUM(BlueprintType)
enum class E_AITypes : uint8
{
	NONE		UMETA(DisplayName = "None"),
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

//Enum Sense
UENUM(BlueprintType)
enum class E_AISense : uint8
{
	NONE			UMETA(DisplayName = "None"),
	SIGHT			UMETA(DisplayName = "Sight"),
	HEARING			UMETA(DisplayName = "Hearing"),
	TOUCH			UMETA(DisplayName = "Touch")
};
