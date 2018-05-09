// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::BeginPlay() {
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTrack();
	ApplySideForce();
	ThrottleToDrive = 0;
}

void UTankTrack::SetThrottle(float Throttle) {
	ThrottleToDrive = FMath::Clamp<float>(ThrottleToDrive + Throttle, -1, 1);
	
}

void UTankTrack::DriveTrack()
{
	FVector ForceApplied = TankMaxDrivingForce * ThrottleToDrive*GetForwardVector();
	FVector ForceLocation = GetSocketLocation(FName("ForceLocation"));
	UPrimitiveComponent* RootCompoent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	RootCompoent->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::ApplySideForce()
{
	UPrimitiveComponent* RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//�ҵ�̹�����ڵ��ƶ�������ٶ�
	FVector TankVelocity = RootComponent->GetComponentVelocity();
	FVector RightVector = RootComponent->GetRightVector();
	//�ҵ�̹�˲໬�ٶ�
	float SideSpeed = FVector::DotProduct(RightVector, TankVelocity);
	//�ҵ�̹�˲໬��Ӧ�ü��ٶ�
	float DeltaTime = GetWorld()->DeltaTimeSeconds;
	auto SideSpeedAccleration = SideSpeed / DeltaTime * GetRightVector()*-1;
	//�õ������������F=ma
	auto CorrectionForce = (RootComponent->GetMass()*SideSpeedAccleration) / 2;
	RootComponent->AddForce(CorrectionForce);


}


