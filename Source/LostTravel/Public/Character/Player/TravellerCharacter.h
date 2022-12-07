// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "TravellerCharacter.generated.h"

class UInputAction;
class UInputMappingContext;
class ACameraActor;

UCLASS()
class LOSTTRAVEL_API ATravellerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATravellerCharacter();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerCamera")
	TSubclassOf<ACameraActor> FollowCameraClass;

	UPROPERTY()
	ACameraActor* FollowCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerInput")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerInput")
	UInputAction* MoveForwardAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerInput")
	UInputAction* MoveRightAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerInput")
	UInputAction* JumpAction;

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "PlayerInput")
	void MoveForward(const FInputActionValue& ActionVal);

	UFUNCTION(BlueprintCallable, Category = "PlayerInput")
	void MoveRight(const FInputActionValue& VActionValal);
};
