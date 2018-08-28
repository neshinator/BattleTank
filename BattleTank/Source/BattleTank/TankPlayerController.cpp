// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Public/Tank.h"
#include "Engine/World.h"

#define OUT

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled Tank Cannot be found"))
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; //Out parameter
	if (GetSightRayHitLocation(HitLocation)) //Has "side effect", is going to line trace
	{
		//Tell controlled tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);
	}
}

//Get world location of linetrace through crosshair, true if it hits land
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	//"De-project" the scren position of the crosshair to the world position
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		//line trace along that look direction, and see whwat we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return true;
}

//"De-project" the screen position of the crosshair to the world position
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector WorldLocation; //we are ignoring this
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, OUT WorldLocation, OUT LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
			OUT HitResult,
			OUT StartLocation,
			OUT EndLocation,
			ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}


