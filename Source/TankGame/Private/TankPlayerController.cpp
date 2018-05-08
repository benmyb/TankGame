// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


ATank* ATankPlayerController::GetControlledTank() {

	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	if (ControlledTank == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("ERROR:Controllled Tank is NULL!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Controllled Tank is %s"),*ControlledTank->GetName());
	}
}