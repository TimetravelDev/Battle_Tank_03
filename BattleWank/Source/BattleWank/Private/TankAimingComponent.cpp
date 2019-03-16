// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	 // ..
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankBarrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!TankBarrel) { return; }
	// this - tankaimingcomponent is a uobject
	FVector OutLaunchVelocity(0);
	FVector StartLocation = TankBarrel->GetSocketLocation(FName("LaunchPoint"));

	// automated solution to calculate shell trajectory
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this, 
		OutLaunchVelocity, 
		StartLocation, 
		HitLocation, 
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	auto Time = GetWorld()->GetTimeSeconds();

	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);

		auto OurTankName = GetOwner()->GetName();
		// auto BarrelLocation = TankBarrel->GetComponentLocation();
		// UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString());
		
		UE_LOG(LogTemp, Warning, TEXT("%f: Aiming Solution Found"), Time);
	}
	else
	{
 		UE_LOG(LogTemp, Warning, TEXT("%f: No aiming solution"), Time);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// work out difference between the current barrel rotation and AimDirection
	auto BarrelRotator = TankBarrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	// Move the barrel the right amount this frame
	// Given a max elevation speed and the frame time
	TankBarrel->Elevate(DeltaRotator.Pitch);
}
