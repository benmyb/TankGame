// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TANKGAME_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
	
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* CollisionMesh = nullptr;
	//发射炮弹粒子效果
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* LaunchParticle = nullptr;
	//击中物体粒子效果
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* ImpactParticle = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		URadialForceComponent* ExplosionForce = nullptr;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float ProjectileBaseDamage = 20.0f;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float ProjectileMinimumDamage = 5.0f;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float ProjectileDamageFallOff = 0.05f;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float ProjectileDamageInnerRadius = 10.0f;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float ProjectileDamageOuterRadius = 500.0f;

	void LaunchProjectile(float Speed);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
