// Fill out your copyright notice in the Description page of Project Settings.

#include "PippleGameModeBase.h"


void APippleGameModeBase::StartPlay() {
	Super::StartPlay();

	if (GEngine) {
		//Displays a debug message 5s,
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello Torben, this is PippleGameMode - Debugmessage"));
	}
}

