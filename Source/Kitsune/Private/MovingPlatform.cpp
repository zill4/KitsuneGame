// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	// When override a class make sure to use super at the beginning.
	Super::Tick(DeltaTime);


	if (HasAuthority())
	{
		FVector Location = GetActorLocation();
		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();

		Location += Speed * Direction * DeltaTime;
		SetActorLocation(Location);

		float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
		float JourneyTravelled = (Location - GlobalStartLocation).Size();
		if (JourneyTravelled >= JourneyLength)
		{
			FVector Temp = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = Temp;
		}
	}

}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// Not valid to set replicate on client, consider that this code is being ran on both client and server
	// thus there should be a differentiation of who can run what within the code.
	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);


	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

}