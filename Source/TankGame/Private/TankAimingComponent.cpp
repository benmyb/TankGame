// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::Initalize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (Barrel == nullptr || Turret == nullptr)return;

	FVector FireVector;
	FVector StartLocation = Barrel->GetSocketLocation(FName("FireLocation"));

	bool bHaveSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		FireVector,
		StartLocation,
		HitLocation,
		LaunachSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveSolution) {
		//֪ͨ�������ڹ���ת
		//UE_LOG(LogTemp, Warning, TEXT("Fire Vector:%s"), *FireVector.GetSafeNormal().ToString());
		Turret->MoveTurret(FireVector.GetSafeNormal());
		Barrel->MoveBarrel(FireVector.GetSafeNormal());
	}
}

void UTankAimingComponent::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire!"));
	if (Barrel == nullptr || ProjectileType == nullptr)return;

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileType,
		Barrel->GetSocketLocation(FName("FireLocation")),
		Barrel->GetSocketRotation(FName("FireLocation"))
		);
	Projectile->LaunchProjectile(LaunachSpeed);
}

