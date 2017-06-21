// Fill out your copyright notice in the Description page of Project Settings.

#include "CloneOfTanks.h"
#include "Public/TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Safe Clamping speed
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	// Calculating elevation change
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewElevation = FMath::Clamp<float>(RelativeRotation.Pitch + ElevationChange, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(NewElevation, 0.f, 0.f));
}


