// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Public/Tank.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CLONEOFTANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:

	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;

	ATank* GetPlayerTank() const;
};
