// Fill out your copyright notice in the Description page of Project Settings.

#include "CloneOfTanks.h"
#include "TankPlayerController.h"
#include "Public/TankAimingComponent.h"
#include "Public/Tank.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller : Aiming Component not found."));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	auto Pawn = GetPawn();

	if (!Pawn) { return; }

	auto AimingComponent = Pawn->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) return;

	FVector HitLocation; // out parameter

	if (GetSightRayHitLocation(HitLocation)) {
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	FVector LookDirection;
	if (GetLookDirection(LookDirection))
	{
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector& LookDirection) const
{
	// Get Viewport size
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	// Get screen location in pixels
	FVector2D ScreenLocation(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// De-Project screen position to a world direction
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(const FVector &LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, StartLocation + LookDirection * LineTraceRange, ECollisionChannel::ECC_Visibility);

	if (HitResult.GetActor()) {
		//UE_LOG(LogTemp, Warning, TEXT("Hitting %s"), *HitResult.GetActor()->GetName());
		HitLocation = HitResult.Location;
		return true;
	}
	else {
		return false;
	}
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}