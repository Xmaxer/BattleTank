// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	ATank* PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found player tank: %s"), *(PlayerTank->GetName()));
	}
}

ATank * ATankAIController::GetPlayerTank() const
{
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if (!PlayerPawn)
	{
		return nullptr;
	}
	else
	{
		return Cast<ATank>(PlayerPawn);
	}
}

ATank* ATankAIController::GetAIControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}