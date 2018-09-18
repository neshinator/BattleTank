// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerTank)
	{
		auto ControlledTank = Cast<ATank>(GetPawn());
		if (!ControlledTank) { return; }

		//Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); //check radius is cm

		//Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//Fire if ready
		ControlledTank->Fire();
	}
}


