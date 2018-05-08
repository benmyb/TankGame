// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::MoveBarrel(FVector AimDirection)
{
	FRotator CurrentRotation = GetForwardVector().Rotation();
	FRotator AimRotation = AimDirection.Rotation();

	float ChangeYaw = AimRotation.Pitch - CurrentRotation.Pitch;
	float RelativeSpeed = FMath::Clamp<float>(ChangeYaw, -1, 1);
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond*GetWorld()->DeltaTimeSeconds;
	float NewRotationPitch = RotationChange + RelativeRotation.Pitch;
	//ÅÚ¹Ü¸©Ñö½ÇÏÞÖÆ
	NewRotationPitch= FMath::Clamp<float>(NewRotationPitch, MinDegree, MaxDegree);
	SetRelativeRotation(FRotator(NewRotationPitch, 0, 0));
}
