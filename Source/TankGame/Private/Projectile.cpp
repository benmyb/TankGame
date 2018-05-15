// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	ProjectileMovementComponent->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionMesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(true);

	LaunchParticle = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchParticle"));
	LaunchParticle->AttachTo(RootComponent);
	LaunchParticle->SetAutoActivate(false);
	
	
	ImpactParticle = CreateDefaultSubobject<UParticleSystemComponent>(FName("ImpactParticle"));
	ImpactParticle->AttachTo(RootComponent);
	ImpactParticle->SetAutoActivate(false);

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("ExplosionForce"));
	ExplosionForce->AttachTo(RootComponent);
	ExplosionForce->SetAutoActivate(false);


}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector*Speed);
	ProjectileMovementComponent->Activate();
	LaunchParticle->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	//ÅÚµ¯ÃüÖÐºó
	ImpactParticle->Activate();

	CollisionMesh->SetNotifyRigidBodyCollision(false);
	SetRootComponent(ImpactParticle);
	CollisionMesh->DestroyComponent();

	ExplosionForce->FireImpulse();

	UGameplayStatics::ApplyRadialDamageWithFalloff(
		this,
		ProjectileBaseDamage,
		ProjectileMinimumDamage,
		GetActorLocation(),
		ProjectileDamageInnerRadius,
		ProjectileDamageOuterRadius,
		ProjectileDamageFallOff,
		UDamageType::StaticClass(),
		TArray<AActor*>()
	);
}

