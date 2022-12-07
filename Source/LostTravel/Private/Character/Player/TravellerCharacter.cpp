// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/TravellerCharacter.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Camera/CameraActor.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ATravellerCharacter::ATravellerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ATravellerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PC = CastChecked<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputSystem = 
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			if (InputMappingContext)
			{
				EnhancedInputSystem->AddMappingContext(InputMappingContext, 100);
			}
		}
	}

	if (UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		if (MoveForwardAction)
		{
			EIC->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ATravellerCharacter::MoveForward);
		}
		if (MoveRightAction)
		{
			EIC->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ATravellerCharacter::MoveRight);
		}
		if (JumpAction)
		{
			EIC->BindAction(JumpAction, ETriggerEvent::Started, this, &ATravellerCharacter::Jump);
		}
	}
}

void ATravellerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (ensure(FollowCameraClass))
	{
		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FollowCamera = GetWorld()->SpawnActor<ACameraActor>(FollowCameraClass, GetActorTransform(), Params);
	}
}

void ATravellerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATravellerCharacter::MoveForward(const FInputActionValue& ActionVal)
{
	AddMovementInput(-FVector::RightVector, ActionVal.Get<float>());
}

void ATravellerCharacter::MoveRight(const FInputActionValue& ActionVal)
{
	AddMovementInput(FVector::ForwardVector, ActionVal.Get<float>());
}