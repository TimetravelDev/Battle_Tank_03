// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLEWANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 10;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 40;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = 0;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxRelativeSpeed = 1;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinRelativeSpeed = -1;

public:
	// -1 is max downward speed, +1 is max upward speed
	void Elevate(float RelativeSpeed);
};
