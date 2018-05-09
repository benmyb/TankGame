// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h"

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

	virtual void BeginPlay() override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//油门
	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float Throttle);//[-1,1]
	UPROPERTY(EditAnywhere, Category = "Setup")
		float TankMaxDrivingForce = 40000000.0f;
	
	float ThrottleToDrive = 0.0f;
	//开车
	void DriveTrack();
	//消除坦克漂移效果
	void ApplySideForce();
	
};
