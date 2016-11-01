// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "StageCamera.generated.h"

UCLASS()
class NOTSTREETFIGHTER_API AStageCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStageCamera();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
    
private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta= (AllowPrivateAccess = "true"))
    UCameraComponent* FightCamera;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta= (AllowPrivateAccess = "true"))
    USpringArmComponent* CameraBoom;
public:
    UCameraComponent* GetCamera() {return FightCamera;}
};
