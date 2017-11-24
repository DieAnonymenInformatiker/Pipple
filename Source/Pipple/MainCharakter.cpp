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

}

// Called to bind functionality to input
void AMainCharakter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharakter::MoveForward);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharakter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMainCharakter::StopJump);
}




void AMainCharakter::MoveForward(float Value) {
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AMainCharakter::StartJump() {
	bPressedJump = true;
}

void AMainCharakter::StopJump() {
	bPressedJump = false;
}

