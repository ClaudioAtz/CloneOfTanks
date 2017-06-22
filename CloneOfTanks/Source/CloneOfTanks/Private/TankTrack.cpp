// Fill out your copyright notice in the Description page of Project Settings.

#include "CloneOfTanks.h"
#include "Public/TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	
	UE_LOG(LogTemp, Warning, TEXT("%s applying force of %s"), *GetName(), *ForceApplied.ToString());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}