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

//Initializing the USpringArmComponent attribute
SpringArm = PCIP.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));

//Adding the springArm to the Character's RootComponent (the collision capsule)
SpringArm->AttachTo(RootComponent);

//bAbsoluteRotation allows us to define if this support will rotate with the player or will stay fixed.
//In our case we don't want it to rotate with the character.
SpringArm->bAbsoluteRotation = true;

//The distance between the arm and its target. This value defines the distance between the character and the camera.
//Try out different values to see the outcome.
SpringArm->TargetArmLength = 500.f;

//Socket Offset.
//Socket is an anchor point to other components.
//For instance, in the character case we can define the socket in the character's hand
//this way we can add another component(for example a gun).
//But in our case we will add a camera to our SpringArm
SpringArm->SocketOffset = FVector(0.f, 0.f, 75.f);

//The relative rotation of the arm regard to its parent.
//We want the camera rotated 180 degrees in the Y axis in order to be situated parallel to the character, at the same level.
//This way we achieve the classic side-scroller camera's style.
SpringArm->RelativeRotation = FRotator(0.f, 180.f, 0.f);

// Creating the UCameraComponent instance.
SideViewCamera = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("SideViewCamera"));

//The AttachTo method allow us to add an object to another in a given socket. It receives two parameters,
//the first one, the object where we will be anchored (the springArm) and the second the socket's name where we will be anchored.
//USpringArmComponent's SocketName returns the name of the components socket.
SideViewCamera->AttachTo(SpringArm, USpringArmComponent::SocketName);