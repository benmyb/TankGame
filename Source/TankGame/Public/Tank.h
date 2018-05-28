// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class TANKGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Tank")
	float GetHealthPercentage();

	FTankDelegate OnDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team")
		bool TeamFlag = true;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float FireRadius = 5000.0f;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float AimRadius = 10000.0f;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float TraceRadius = 3000.0f;
private:
	UPROPERTY(EditAnywhere, Category = "Health")
		float MaxHp = 100.0f;
	UPROPERTY(VisibleAnywhere, Category = "Health")
		float CurrentHp = MaxHp;
};
