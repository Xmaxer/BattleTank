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

	//UE_LOG(LogTemp, Warning, TEXT("Player controller ticking"));
}
void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }


	//Get world location through crosshair

	FVector HitLocation; //OUT param

	if (GetRayHitLocation(HitLocation))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString());
	}
	//if hits something
	//aim towards point
}
bool ATankPlayerController::GetRayHitLocation(FVector & HitLocation)
{
	//Find crosshair position

	int32 SizeX, SizeY;
	GetViewportSize(SizeX, SizeY);

	FVector2D ScreenLocation = FVector2D(SizeX * CrosshairX, SizeY * CrosshairY);

	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());

	// De-projection
	FVector WorldDirection, WorldLocation;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("Pointing crosshair at: %s"), *WorldDirection.ToString());
	}
	//Line trace along the look direction
	return true;
}
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}



