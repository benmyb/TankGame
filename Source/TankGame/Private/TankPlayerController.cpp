// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::Tick(float DeltaTime)
{
	//�ƶ���������׼λ��
	AimToTarget();
}

ATank* ATankPlayerController::GetControlledTank() {

	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimToTarget()
{
	//����õ���׼���ƶ����÷�λ
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		//�м��е�Ŀ��
		//UE_LOG(LogTemp, Warning, TEXT("Hit location:%s"),*HitLocation.ToString());
		GetControlledTank()->FindComponentByClass<UTankAimingComponent>()->AimAt(HitLocation);

	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation)
{
	int32 ViewportSizeX, ViewportSizeY;
	//��Ļ��С
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX*CrosshairXLocation, ViewportSizeY*CrosshairYLocation);
	FVector WorldLocation;
	FVector WorldDirection;

	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection)) {
		//ʹ��������ײ����
		if(GetLookVectorHitLocation(WorldDirection,OutHitLocation))
		return true;
	}
	return false;
}

//Ѱ������ײ���ĵ�
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & OutHitLocation)
{
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + LookDirection * LineTraceRange;
	FHitResult HitResult;

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	)) {
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0.0f);
	return false;
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