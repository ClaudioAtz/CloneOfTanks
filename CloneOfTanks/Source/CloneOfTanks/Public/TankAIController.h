// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class CLONEOFTANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetPawn(APawn* InPawn) override;

	// Get reference to player tank
	APawn* GetPlayerTank() const;

	UFUNCTION()
	void OnPossessedTankDeath();

protected:
	// How close can the AI tank get
	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 30.f;

public:

	void AimTowardsPlayer() const;
};
