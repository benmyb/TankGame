// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("ERROR:Player Tank is NULL!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Tank is %s"), *PlayerTank->GetName());
	}
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto ProcessTank = Cast<ATank>(InPawn);
		if (!ProcessTank)return;
		ProcessTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnControlledTankDeath);
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (GetControlledTank()) {
	//	//让坦克向玩家移动
	//	//UE_LOG(LogTemp, Warning, TEXT("Player Tank at %s"), *GetPlayerTank()->GetActorLocation().ToString());
	//	MoveToActor(GetPlayerTank(), AcceptanceRadius);

	//	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	//	AimingComponent->AimAt(GetPlayerTank()->GetActorLocation());
	//	if (AimingComponent->FiringState == EFiringState::Locked) {
	//		AimingComponent->Fire();
	//	}
	//}
	TArray<AActor*> FoundActors;
	ATank* Target = nullptr;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATank::StaticClass(), FoundActors);
	TArray<unsigned> enemy;
	ATank* controlledTank = GetControlledTank();
	if (controlledTank == nullptr)return;

	bool myteam = controlledTank->TeamFlag;
	int actorNum = FoundActors.Num();
	for (int i = 0; i < actorNum; ++i) {
		if (Cast<ATank>(FoundActors[i])->TeamFlag == myteam)continue;
		else enemy.Push(i);
	}
	if (enemy.Num() == 0)return;
	int index = FMath::RoundToInt(FMath::FRandRange(0, enemy.Num() - 1));
	index = enemy[index];
	Target = Cast<ATank>(FoundActors[index]);

	float distance = FVector::Distance(controlledTank->GetActorLocation(), Target->GetActorLocation());
	bool isInFireRadius = distance <= (controlledTank->FireRadius);
	bool isInAimRadius = distance <= (controlledTank->AimRadius);

	MoveToActor(Target, controlledTank->TraceRadius);
	auto AimingComponent = controlledTank->FindComponentByClass<UTankAimingComponent>();
	if (isInAimRadius)AimingComponent->AimAt(Target->GetActorLocation());
	if (AimingComponent->FiringState == EFiringState::Locked && isInFireRadius) {
		AimingComponent->Fire();
	}
}

ATank * ATankAIController::GetControlledTank() {

	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank()
{
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (PlayerTank == nullptr) {
		return nullptr;
	}
	return PlayerTank;
}

void ATankAIController::OnControlledTankDeath()
{
	//坦克坏掉处理函数
	if (GetControlledTank()) {
		GetControlledTank()->DetachFromControllerPendingDestroy();
	}
}
