// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

ATank* ATankAIController::GetAIControlledTank() const { return Cast<ATank>(GetPawn()); }

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto LogAITank = GetAIControlledTank();
	if (!LogAITank)
	{
		UE_LOG(LogTemp, Warning, TEXT("No valid AI tank! Bad!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank is:  %s"), *(LogAITank->GetName()));
	}
}