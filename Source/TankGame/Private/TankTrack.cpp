// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle) {
	FVector ForceApplied = TankMaxDrivingForce * Throttle*GetForwardVector();
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* RootCompoent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	RootCompoent->AddForceAtLocation(ForceApplied, ForceLocation);
}


