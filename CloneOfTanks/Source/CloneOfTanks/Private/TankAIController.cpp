// Fill out your copyright notice in the Description page of Project Settings.

#include "CloneOfTanks.h"
#include "Public/TankAIController.h"
#include "Public/TankAimingComponent.h"
#include "Public/Tank.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetPlayerTank();

	if (ensure(PlayerTank && GetPawn()))
	{
		MoveToActor(PlayerTank, AcceptanceRadius);

		AimTowardsPlayer();

		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		if (!ensure(AimingComponent)) return;

		// Fire only if locked
		if (AimingComponent->GetFiringState() == EFiringStatus::Locked) {
			AimingComponent->Fire();
		}
	}
}

APawn* ATankAIController::GetPlayerTank() const
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return nullptr;

	return PlayerController->GetPawn();
}

void ATankAIController::AimTowardsPlayer() const {

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) return;

	AimingComponent->AimAt(GetPlayerTank()->GetActorLocation());
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	auto Pawn = GetPawn();
	if (Pawn) {
		Pawn->DetachFromControllerPendingDestroy();
	}
}