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
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank* GetControlledTank();
	void AimToTarget();
	//�õ����߼��е�Ŀ��������bool��ʾ��û�м�����һ��Ŀ����
	bool GetSightRayHitLocation(FVector &OutHitLocation);
	//�����������е�λ��
	bool GetLookVectorHitLocation(FVector LookDirection, FVector &OutHitLocation);
	
private:
	//׼������λ��ռ��Ļ����
	float CrosshairXLocation = 0.5f;
	float CrosshairYLocation = 0.3f;
	//��׼��Χ
	UPROPERTY(EditAnywhere)
		float LineTraceRange = 100000.0f;
};
