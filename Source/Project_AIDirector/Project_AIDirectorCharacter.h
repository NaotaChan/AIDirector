// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Project_AIDirectorCharacter.generated.h"

class AProject_AIDirectorPlayerController;

UCLASS(Blueprintable)
class AProject_AIDirectorCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AProject_AIDirectorCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UPROPERTY(BlueprintReadOnly, Category = Player)
	AProject_AIDirectorPlayerController* PlayerController;

protected:
	//Overrides the base function to bind input actions to C++ methods
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Pointer to the Enhanced Input Action asset, editable in the Blueprint editor 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* WhistleAction;

	//Callback function triggered when the whistle input action is executed 
	void OnWhistleTriggered();
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
};

