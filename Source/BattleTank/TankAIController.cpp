// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"



ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("There is no controlled tank!"))
		return;
	}

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("There is no player tank!"))
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("The AI has possessed a tank, and it is %s"), *ControlledTank->GetName())
	UE_LOG(LogTemp, Warning, TEXT("The AI has found the player, and it is %s"), *PlayerTank->GetName())

}

