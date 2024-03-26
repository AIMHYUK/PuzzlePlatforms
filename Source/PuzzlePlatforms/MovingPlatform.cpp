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
        FVector GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation); //트랜스폼 액터를 가져와서 변환
        FVector Direction = (GlobalTargetLocation - Location).GetSafeNormal(); //벡터 정규화, 숫자가 작을때도 보호해줌
	    Location += Speed * DeltaTime * Direction;
        SetActorLocation(Location); 
    }
}


