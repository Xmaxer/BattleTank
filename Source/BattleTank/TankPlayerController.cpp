// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("No tank possesed by PlayerController"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing tank: %s"), *(ControlledTank->GetName()));
	}
}
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}
void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }


	//Get world location through crosshair

	FVector HitLocation; //OUT param

	if (GetRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
	//if hits something
	//aim towards point
}
bool ATankPlayerController::GetRayHitLocation(FVector& HitLocation)
{
	//Find crosshair position

	int32 SizeX, SizeY;
	GetViewportSize(SizeX, SizeY);

	FVector2D ScreenLocation = FVector2D(SizeX * CrosshairX, SizeY * CrosshairY);

	// De-projection
	FVector WorldDirection, WorldLocation;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection))
	{
		return GetLookVectorHitLocation(WorldDirection, HitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector WorldDirection, FVector& HitLocation)
{
	FHitResult hit;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LineTraceRange * WorldDirection);

	if (GetWorld()->LineTraceSingleByChannel(hit, StartLocation, EndLocation, ECC_Visibility))
	{
		HitLocation = hit.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}



