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
	
	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;
	
	
};
