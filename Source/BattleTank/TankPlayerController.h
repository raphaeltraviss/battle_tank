// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

struct AimLine {
	FVector Start;
	FVector End;
};

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
	virtual void Tick(float DeltaSeconds) override;
	
private:
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	void AimTowardsCrosshair();
	AimLine GetAimLine() const;
	bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333;
	
	
};
