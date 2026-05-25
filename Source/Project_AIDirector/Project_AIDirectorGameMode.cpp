// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_AIDirectorGameMode.h"
#include "Project_AIDirectorPlayerController.h"
#include "Project_AIDirectorCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProject_AIDirectorGameMode::AProject_AIDirectorGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AProject_AIDirectorPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ProjectFolder/Player/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/ProjectFolder/Player/BP_PlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}