// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCharakter.h"


// Sets default values
AMainCharakter::AMainCharakter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainCharakter::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Maincharacter chosen"));
	}
	
}

// Called every frame
void AMainCharakter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const FVector CurrentPosition = GetActorLocation();
	if (CurrentPosition.Z < -10.0f) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("U FAILED"));
		FVector StartPosition =  FVector(0.0, 0.0, 112.0);
		SetActorLocation(StartPosition, false);
	}
	
	

}

// Called to bind functionality to input
void AMainCharakter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharakter::MoveForward);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharakter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMainCharakter::StopJump);
	PlayerInputComponent->BindAction("UseFloatingPower",IE_Pressed, this, &AMainCharakter::FloatingPower);
	PlayerInputComponent->BindAction("UseFloatingPower", IE_Repeat, this, &AMainCharakter::FloatingPower);
}


void AMainCharakter::FloatingPower() {
	FVector pos = GetActorLocation();
	pos.Z += 40;
	AMainCharakter::SetActorLocation(pos, false);

}


void AMainCharakter::MoveForward(float Value) {
	movementSpeed += (Value * 0.005);
	if (Value == 0)
		movementSpeed *= 0.9;

	FString movementOutput = FString::SanitizeFloat(movementSpeed);
	if (movementSpeed != 0.0) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, *movementOutput);
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, movementSpeed);
}

void AMainCharakter::StartJump() {
	bPressedJump = true;
}

void AMainCharakter::StopJump() {
	bPressedJump = false;
}

