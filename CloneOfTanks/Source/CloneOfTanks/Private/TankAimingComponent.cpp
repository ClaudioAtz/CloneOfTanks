// Fill out your copyright notice in the Description page of Project Settings.

#include "CloneOfTanks.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Public/TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::AimAt(const FVector& WorldSpaceAim, float LaunchSpeed)
{
	if (!Barrel || !Turret) return;

	FVector LaunchVelocity, AimDirection(-1, 0, 0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate out launch velocity
	if (UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, StartLocation, WorldSpaceAim, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace)) 
	{
		AimDirection = LaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("%f %s aiming at %s"), GetWorld()->GetTimeSeconds(), *GetOwner()->GetName(), *AimDirection.ToString());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%f %s suggestion failed at %s"), GetWorld()->GetTimeSeconds(), *GetOwner()->GetName(), *AimDirection.ToString());
	}

	MoveBarrelTowards(AimDirection);
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(const FVector &AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}
