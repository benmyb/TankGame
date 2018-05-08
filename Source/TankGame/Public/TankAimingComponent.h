// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankBarrel.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initalize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	void AimAt(FVector HitLocation);
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float LaunachSpeed = 100000.0f;

	
};
