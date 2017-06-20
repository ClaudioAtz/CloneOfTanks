// Fill out your copyright notice in the Description page of Project Settings.

#include "CloneOfTanks.h"
#include "Public/TankBarrel.h"
#include "Public/TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::AimAt(const FVector& WorldSpaceAim, float LaunchSpeed)
{
	if (!Barrel) return;

	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate out launch velocity
	if (UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, StartLocation, WorldSpaceAim, LaunchSpeed, ESuggestProjVelocityTraceOption::DoNotTrace)) 
	{
		auto AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *GetOwner()->GetName(), *AimDirection.ToString());
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(const FVector &AimDirection)
{
	Barrel->Elevate(5);
}
