// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "Project_AIDirectorPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class AProject_AIDirectorCharacter;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class AProject_AIDirectorPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AProject_AIDirectorPlayerController();

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* CustomMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ZoomAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	UPROPERTY(BlueprintReadOnly, Category = Player)
	AProject_AIDirectorCharacter* PlayerRef;

	/******* TEAM ID ******/
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;

	virtual FGenericTeamId GetGenericTeamId() const override;
	/******* END TEAM ID ******/

	UFUNCTION(BlueprintPure, Category = "Hiding")
	bool GetIsHiding() const { return IsHiding; }

	UFUNCTION(BlueprintCallable, Category = "Hiding")
	void SetIsHiding(bool IsNowHiding);

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Zoom(const FInputActionValue& Value);
	void StartSprint(const FInputActionValue& Value);
	void StopSprint(const FInputActionValue& Value);

	/******* TEAM ID ******/
	FGenericTeamId TeamID;

private:

	UPROPERTY(BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	int CameraPositionInt;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	int MaxCameraPositionInt;

	UPROPERTY(BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float DefaultTargetArmLength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float CameraZoomDifference;

	UPROPERTY(BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	bool IsSprinting;

	UPROPERTY(BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	bool IsHiding;
};


