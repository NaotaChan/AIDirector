#pragma once

//Enum Cone Sight Zones
UENUM(BlueprintType)
enum class E_SightConeZones : uint8
{
	NONE			UMETA(DisplayName = "None"),
	NOTSEEN			UMETA(DisplayName = "NotSeen"),
	BACKWARD		UMETA(DisplayName = "Backward"),
	PERIPHERAL		UMETA(DisplayName = "Peripheral"),
	WIDE			UMETA(DisplayName = "Wide"),
	NARROW			UMETA(DisplayName = "Narrow")
};