// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Tank is: %s"), *PlayerTank->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Tank Cannot be found"))
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		//Todo: Move towards the player

		//Aim towards the player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		//Fire if ready
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}

