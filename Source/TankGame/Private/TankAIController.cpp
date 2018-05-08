// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("ERROR:Player Tank is NULL!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Tank is %s"), *PlayerTank->GetName());
	}
}

ATank * ATankAIController::GetControlledTank() {

	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank()
{
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (PlayerTank == nullptr) {
		return nullptr;
	}
	return PlayerTank;
}
