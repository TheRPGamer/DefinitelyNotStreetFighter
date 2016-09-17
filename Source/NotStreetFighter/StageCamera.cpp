// Fill out your copyright notice in the Description page of Project Settings.

#include "NotStreetFighter.h"
#include "StageCamera.h"



// Sets default values
AStageCamera::AStageCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("FightCameraSpringArm"));
    CameraBoom->TargetArmLength = 600.0f;
    CameraBoom->bAbsoluteRotation =true;
    CameraBoom->bDoCollisionTest = false;
    CameraBoom->RelativeRotation = FRotator(0.0f, -90.0f, 0.0f);
    
    //Create Camera
    FightCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FightCamera"));
    FightCamera->ProjectionMode = ECameraProjectionMode::Orthographic;
    FightCamera->OrthoWidth = 2048.0f;
    FightCamera->bAutoActivate = true;
    

}

// Called when the game starts or when spawned
void AStageCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStageCamera::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

