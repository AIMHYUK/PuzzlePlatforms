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

    GlobalStartLocation = GetActorLocation(); //시작점
    GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation); //끝점, 트랜스폼 액터를 가져와서 변환
}
void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(HasAuthority())//true면 서버, false면 클라이언트
    {
        FVector Location = GetActorLocation();
        float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size(); //움직일 거리
        float JourneyTravelled = (Location - GlobalStartLocation).Size(); //움직인 거리
        FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal(); //벡터 정규화, 숫자가 작을때도 보호해줌
        Location += Speed * DeltaTime * Direction;
        SetActorLocation(Location); 
	    if(JourneyTravelled >= JourneyLength ) //움직인 거리가 움직일 거리보다 커지면 시작점과 끝점 교환
        {
            FVector Swap = GlobalTargetLocation; 
            GlobalTargetLocation = GlobalStartLocation;
            GlobalStartLocation = Swap;
        }       
    }
}


