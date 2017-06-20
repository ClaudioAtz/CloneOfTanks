// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "Public/Tank.h"
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

	// Get reference to controlled tank
	ATank* GetControlledTank() const;

	// Get reference to player tank
	ATank* GetPlayerTank() const;

public:

	void AimTowardsPlayer() const;
};
