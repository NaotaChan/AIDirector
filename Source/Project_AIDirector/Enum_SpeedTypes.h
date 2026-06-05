#pragma once

UENUM(BlueprintType)
enum class E_AISpeedType : uint8
{
	UNSET	UMETA(DisplayName = "Unset"),
	WALK	UMETA(DisplayName = "Walk"),
	RUN		UMETA(DisplayName = "Run")
};