// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	ATank* GetControlledTank() const;
	
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
private:
	void AimTowardsCrosshair();

	bool GetRayHitLocation(FVector& HitLocation);

	bool GetLookVectorHitLocation(FVector WorldDirection, FVector& HitLocation);

	UPROPERTY(EditAnywhere)
	float CrosshairX = 0.5, CrosshairY = 0.3333, LineTraceRange = 1000000;
};
