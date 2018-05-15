// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto ProcessTank = Cast<ATank>(InPawn);
		if (!ProcessTank)return;
		ProcessTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnControlledTankDeath);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	//移动炮塔到瞄准位置
	AimToTarget();
}

ATank* ATankPlayerController::GetControlledTank() {

	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimToTarget()
{
	//如果得到瞄准，移动到该方位
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		//有集中的目标
		//UE_LOG(LogTemp, Warning, TEXT("Hit location:%s"),*HitLocation.ToString());
		GetControlledTank()->FindComponentByClass<UTankAimingComponent>()->AimAt(HitLocation);

	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation)
{
	int32 ViewportSizeX, ViewportSizeY;
	//屏幕大小
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX*CrosshairXLocation, ViewportSizeY*CrosshairYLocation);
	FVector WorldLocation;
	FVector WorldDirection;

	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection)) {
		//使用射线找撞击点
		if(GetLookVectorHitLocation(WorldDirection,OutHitLocation))
		return true;
	}
	return false;
}

//寻找视线撞击的点
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

void ATankPlayerController::OnControlledTankDeath()
{
	//坦克坏掉处理函数

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