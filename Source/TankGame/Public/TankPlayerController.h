// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void SetPawn(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank* GetControlledTank();
	void AimToTarget();
	//得到视线集中的目标向量，bool表示有没有集中在一个目标上
	bool GetSightRayHitLocation(FVector &OutHitLocation);
	//视线向量击中的位置
	bool GetLookVectorHitLocation(FVector LookDirection, FVector &OutHitLocation);
	UFUNCTION()
		void OnControlledTankDeath();
	
private:
	//准心所在位置占屏幕比例
	float CrosshairXLocation = 0.5f;
	float CrosshairYLocation = 0.3f;
	//瞄准范围
	UPROPERTY(EditAnywhere)
		float LineTraceRange = 100000.0f;
};
