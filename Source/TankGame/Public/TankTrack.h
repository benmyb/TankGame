// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKGAME_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//смце
	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float Throttle);//[-1,1]
	UPROPERTY(EditAnywhere, Category = "Setup")
		float TankMaxDrivingForce = 40000000.0f;
	
	
	
};
