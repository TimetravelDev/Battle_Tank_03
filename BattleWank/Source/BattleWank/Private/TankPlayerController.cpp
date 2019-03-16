// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"

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
	AimToCrosshair();
}

void ATankPlayerController::AimToCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation, GetControlledTank()->LaunchSpeed);
	}
}

ATank* ATankPlayerController::GetControlledTank() const { return Cast<ATank>(GetPawn()); }

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the viewport size and crosshair pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D( (ViewportSizeX * CrossHairXLocation), (ViewportSizeY * CrossHairYLocation) );

	// de-project the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//line trace that crosshair world direction
		//if successful, assign that spot to OutHitLocation
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
		return true;
	}
	else return false;
}

// de-project the screen position of the crosshair to a world direction
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector WorldLocation;	// not used
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection)) return true;
	else return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	// get location of the player's camera
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	// end at where they are looking. max distance of LineTraceRange
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	// if all that works, set the result to HitLocation and return via reference
	if ( GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation,	EndLocation, ECollisionChannel::ECC_Visibility ) )
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else
	{
		HitLocation = FVector(0.0);
		return false;	// failed line trace
	}
}