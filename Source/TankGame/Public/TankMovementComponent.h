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


	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	/** path following: request new move input (normal vector = full strength) */
	//virtual void RequestPathMove(const FVector& MoveInput);
private:
	UTankTrack * LeftTrack = nullptr;
	UTankTrack * RightTrack = nullptr;

};
