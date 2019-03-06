// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"	//must be last in the list

/**
 * 
 */
UCLASS()
class BATTLEWANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;

	void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// move tank barrel to aim at the crosshair's world intersection
	void AimToCrosshair();

private:
	// return an OUT parameter, true if hit location
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
};
