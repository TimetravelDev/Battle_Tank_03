// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

//GETTORS UP TOP
ATank* ATankAIController::GetAIControlledTank() const { return Cast<ATank>(GetPawn()); }

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn) { return Cast<ATank>(PlayerPawn); }
	else { return nullptr; }
}

//Other functions
//Begin play. just logs stuff for now
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

	auto LogPlayerTank = GetPlayerTank();
	if (!LogPlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("No valid Player tank! Bad!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank is:  %s"), *(LogPlayerTank->GetName()));
	}
}


