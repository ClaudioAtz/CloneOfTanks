// Fill out your copyright notice in the Description page of Project Settings.

#include "CloneOfTanks.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Controlling tank %s"), *ControlledTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Not Controlling any tank"));
	}

	auto PlayerTank = GetPlayerTank();
	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("I can see Player tank is %s"), *PlayerTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No player tanks!"));
	}
}

ATank* ATankPlayerController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankPlayerController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


