// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_AIDirectorPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Project_AIDirectorCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISense_Sight.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AProject_AIDirectorPlayerController::AProject_AIDirectorPlayerController()
{
	DefaultTargetArmLength = -1.f;
	CameraZoomDifference = 250.f;
	CameraPositionInt = 3;
	MaxCameraPositionInt = 5;

	SetGenericTeamId(FGenericTeamId(0));
}

//----------------------------------------------------------------------//
// IGenericTeamAgentInterface
//----------------------------------------------------------------------//
void AProject_AIDirectorPlayerController::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	if (TeamID != NewTeamID)
	{
		TeamID = NewTeamID;
		// @todo notify perception system that a controller changed team ID
	}
}

FGenericTeamId AProject_AIDirectorPlayerController::GetGenericTeamId() const
{
	return TeamID;
}

void AProject_AIDirectorPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(CustomMappingContext, 0);
	}

	PlayerRef = Cast<AProject_AIDirectorCharacter>(GetPawn());
	if (IsValid(PlayerRef))
	{
		PlayerRef->PlayerController = this;

		DefaultTargetArmLength = PlayerRef->GetCameraBoom()->TargetArmLength;
		PlayerRef->GetCameraBoom()->TargetArmLength = DefaultTargetArmLength + (CameraZoomDifference * CameraPositionInt);

		PlayerRef->GetCharacterMovement()->MaxWalkSpeed = 230.f;
	}
}

void AProject_AIDirectorPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(PlayerRef) && DefaultTargetArmLength > 0.f)
	{
		PlayerRef->GetCameraBoom()->TargetArmLength = FMath::FInterpTo(PlayerRef->GetCameraBoom()->TargetArmLength, (DefaultTargetArmLength + (CameraZoomDifference * CameraPositionInt)), DeltaTime, 2.f);
	}
}

void AProject_AIDirectorPlayerController::SetIsHiding(bool IsNowHiding)
{
	IsHiding = IsNowHiding;

	if (IsHiding)
	{
		UAIPerceptionSystem::GetCurrent(GetWorld())->UnregisterSource(*PlayerRef, UAISense_Sight::StaticClass());
	}
	else
	{
		UAIPerceptionSystem::RegisterPerceptionStimuliSource(GetWorld(), UAISense_Sight::StaticClass(), PlayerRef);
	}
}

void AProject_AIDirectorPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProject_AIDirectorPlayerController::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProject_AIDirectorPlayerController::Look);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &AProject_AIDirectorPlayerController::Zoom);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AProject_AIDirectorPlayerController::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AProject_AIDirectorPlayerController::StopSprint);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AProject_AIDirectorPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (IsValid(PlayerRef))
	{
		PlayerRef->AddMovementInput(PlayerRef->GetCameraBoom()->GetForwardVector(), MovementVector.Y * 2.f);
		PlayerRef->AddMovementInput(PlayerRef->GetCameraBoom()->GetRightVector(), MovementVector.X);
	}
}

void AProject_AIDirectorPlayerController::Look(const FInputActionValue& Value)
{
	const float LookAxisVector = Value.Get<float>();

	if (IsValid(PlayerRef))
	{
		if (IsInputKeyDown(EKeys::RightMouseButton))
		{
			FRotator Rotator = FRotator(0.f, LookAxisVector, 0.f);
			PlayerRef->GetCameraBoom()->AddWorldRotation(Rotator);
		}
	}
}

void AProject_AIDirectorPlayerController::Zoom(const FInputActionValue& Value)
{
	const float ZoomAxisVector = Value.Get<float>();

	if (ZoomAxisVector > 0)
	{
		CameraPositionInt++;
	}
	else if (ZoomAxisVector < 0)
	{
		CameraPositionInt--;
	}
	CameraPositionInt = FMath::Clamp(CameraPositionInt, 0, MaxCameraPositionInt);

}

void AProject_AIDirectorPlayerController::StartSprint(const FInputActionValue& Value)
{
	const bool SprintValue = Value.Get<bool>();

	if (!IsSprinting)
	{
		PlayerRef->GetCharacterMovement()->MaxWalkSpeed = 500.f;
		IsSprinting = true;
	}
}

void AProject_AIDirectorPlayerController::StopSprint(const FInputActionValue& Value)
{
	if (IsSprinting)
	{
		PlayerRef->GetCharacterMovement()->MaxWalkSpeed = 230.f;
		IsSprinting = false;
	}
}
