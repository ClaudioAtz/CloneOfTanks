// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming states
UENUM()
enum class EFiringStatus : uint8 { Reloading, Aiming, Locked, OutOfAmmo };

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLONEOFTANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(const FVector& WorldSpaceAim);

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable)
	int GetCurrentAmmo() const;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadTimeInSeconds = 5.f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	EFiringStatus GetFiringState() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

	UPROPERTY(EditAnywhere, Category = "Firing")
	int MaxAmmo = 5;

	int CurrentAmmo = 1;

private:

	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;

	/**
	* Function called every frame on this ActorComponent. Override this function to implement custom logic to be executed every frame.
	* Only executes if the component is registered, and also PrimaryComponentTick.bCanEverTick must be set to true.
	*
	* @param DeltaTime - The time since the last tick.
	* @param TickType - The kind of tick this is, for example, are we paused, or 'simulating' in the editor
	* @param ThisTickFunction - Internal tick function struct that caused this to run
	*/
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void MoveBarrelTowards(const FVector &AimDirection);

	bool IsBarrelMoving();

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	double LastFireTime = 0;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000.f; // TODO: Find sensible default
	
	FVector AimDirection;
};
