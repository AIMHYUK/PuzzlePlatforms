// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();

    if(HasAuthority())
    {
        SetReplicates(true);
        SetReplicateMovement(true);
    }
}
void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(HasAuthority())//true면 서버, false면 클라이언트
    {
       	FVector Location = GetActorLocation();
	    Location += FVector(Speed * DeltaTime, 0, 0);
	    SetActorLocation(Location); 
    }

}


