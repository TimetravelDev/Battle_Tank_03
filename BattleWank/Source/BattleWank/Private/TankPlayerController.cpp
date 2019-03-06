// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const { return Cast<ATank>(GetPawn()); }

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

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

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Aim towards Crosshair
}

void ATankPlayerController::AimToCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter
	if ( GetSightRayHitLocation(HitLocation) )
	UE_LOG( LogTemp, Warning, TEXT( "HitLocation: %s"), *HitLocation.ToString() );

	// get world location of linetrace through crosshair
	// TODO: if it hits the landscape, tell controlled tank to aim there
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//line trace the crosshair
	//if it hits the world, set that location to HitLocation, return true
	OutHitLocation = FVector(1.0);

	if ( OutHitLocation == FVector(1.0) )
	{
		return true;
	}
	//otherwise return false
	else
	{
		return false;
	}

}