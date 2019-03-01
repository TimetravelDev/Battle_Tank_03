// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const { return Cast<ATank>(GetPawn()); }

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	auto LogTank = GetControlledTank();
	if (!LogTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("No valid tank! Bad!"));
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("tank is:  %s"), *(LogTank->GetName()) );
	}
}