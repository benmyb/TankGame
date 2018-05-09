// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankTrack.h"

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKGAME_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initalize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);
	UFUNCTION(BlueprintCallable, Category = "Input")
		void MoveForward(float Throttle);
	UFUNCTION(BlueprintCallable, Category = "Input")
		void MoveRight(float Throttle);


private:
	UTankTrack * LeftTrack = nullptr;
	UTankTrack * RightTrack = nullptr;

};
