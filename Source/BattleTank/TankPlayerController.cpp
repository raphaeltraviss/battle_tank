// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter.

	if (GetSightRayHitLocation(HitLocation))
	{
		// Tell the tank to point to this location.
		// UE_LOG(LogTemp, Warning, TEXT("An Actor was hit at %s"), *HitLocation.ToString());

		//@TODO: tell the controlled tank to aim at this point.
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the crosshair position in pixel coordinates.
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(
		ViewportSizeX * CrosshairXLocation,
		ViewportSizeY * CrosshairYLocation
	);

	// Line-trace along that look direction, and report any hit actors.
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		UE_LOG(LogTemp, Warning, TEXT("The world direction is %s"), *LookDirection.ToString())
	}
	

	/*AimLine AimLine = GetAimLine();
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		AimLine.Start,
		AimLine.End,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	AActor* ActorHit = Hit.GetActor();
	if (!ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Nothing is being hit.  "));
		return false;
	}
	OutHitLocation = ActorHit->GetActorLocation();*/

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	// De-project the screen position of the crosshair to a world direction.
	FVector CameraWorldLocation;  // Discarded.
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}

AimLine ATankPlayerController::GetAimLine() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	// we need to find the point projected by the viewpoint dot.

	AimLine result;
	result.Start = PlayerViewPointLocation + PlayerViewPointRotation.Vector();
	result.End = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * 10000000000.00);
	return result;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("There is no controlled tank!"))
		return;
	}
		
	UE_LOG(LogTemp, Warning, TEXT("We are controlling a tank, and it is %s"), *ControlledTank->GetName())

}


