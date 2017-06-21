// Fill out your copyright notice in the Description page of Project Settings.

#include "CloneOfTanks.h"
#include "Public/TankAIController.h"
#include "Public/Tank.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Controlled tank %s"), *ControlledTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Not Controlling any tank"));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank()) 
	{
		AimTowardsPlayer();

		GetControlledTank()->Fire();
	}
}

ATank* ATankAIController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return nullptr;

	auto PlayerPawn = PlayerController->GetPawn();
	if (!PlayerPawn) return nullptr;

	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::AimTowardsPlayer() const {
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}
