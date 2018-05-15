// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void SetPawn(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

	ATank * GetControlledTank();
	ATank* GetPlayerTank();
	
	UPROPERTY(EditAnywhere, Category = "Setup")
		float AcceptanceRadius = 3000.0f;

	UFUNCTION()
		void OnControlledTankDeath();
};
