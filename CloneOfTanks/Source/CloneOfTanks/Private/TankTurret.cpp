// Fill out your copyright notice in the Description page of Project Settings.

#include "CloneOfTanks.h"
#include "Public/TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// Safe Clamping speed
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	// Calculating elevation change
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = FMath::Clamp<float>(RelativeRotation.Yaw + RotationChange, -MaxRotationDegrees, +MaxRotationDegrees);

	SetRelativeRotation(FRotator(0.f, NewRotation, 0.f));
}


