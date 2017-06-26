// Fill out your copyright notice in the Description page of Project Settings.

#include "CloneOfTanks.h"
#include "Public/TankTrack.h"


UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay() {
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, +1);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	UE_LOG(LogTemp, Warning, TEXT("Applying force of %s"), *ForceApplied.ToString());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hitting the ground"));
	DriveTrack();
	ApplySidewaysForce();

	// Reset Throttle
	CurrentThrottle = 0.f;
}

void UTankTrack::ApplySidewaysForce() 
{
	auto TankRoot = GetOwner()->GetRootComponent();

	if (!ensure(TankRoot)) { return; }

	// Calculate slippage speed
	auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	// Work out required acceleration to correct this frame
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	// Calculate and apply side way (F = m * a)
	auto TankMeshComponent = Cast<UStaticMeshComponent>(TankRoot);
	auto CorrectionForce = (TankMeshComponent->GetMass() * CorrectionAcceleration) / 2; // Two tracks

	TankMeshComponent->AddForce(CorrectionForce);
}

