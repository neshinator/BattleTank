// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

//Forward declaration
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

private:
	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	ATank* GetPlayerTank() const;
	
};
