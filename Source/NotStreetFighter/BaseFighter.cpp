// Fill out your copyright notice in the Description page of Project Settings.

#include "NotStreetFighter.h"
#include "BaseFighter.h"


// Sets default values
ABaseFighter::ABaseFighter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    fMaxHP = 100.0f;
    fCurrHP = fMaxHP;
    fCurrentSuperGauge = 100.0f;
    
    iAirdashCounter=0;
    iAirDashLimit = 1;
    iDashCounter = 0;
    iDashLimit = 1;
    iJumpCounter = 0;
    iJumpLimit = 1;
    
    GetCharacterMovement()->GravityScale = 2.0f;
    GetCharacterMovement()->GroundFriction = 3.0f;
    GetCharacterMovement()->JumpZVelocity = 400.0f;
    GetCharacterMovement()->MaxWalkSpeed = 200.0f;
    GetCharacterMovement()->AirControl = 0.9f;
    GetCharacterMovement()->bOrientRotationToMovement = false;
    GetCharacterMovement()->bConstrainToPlane = true;
    //This is for LOCAL space, not world space
    GetCharacterMovement()-> SetPlaneConstraintNormal(FVector(1.0f, 0.0f, 0.0f));
    
}

// Called when the game starts or when spawned
void ABaseFighter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseFighter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ABaseFighter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
    InputComponent->BindAxis("MoveRight", this, &ABaseFighter::MoveHorizontal);
    InputComponent->BindAction("Crouch", IE_Pressed, this, &ABaseFighter::MoveCrouch);
    InputComponent->BindAction("Jumpo", IE_Pressed, this, &ABaseFighter::MoveJump);

}

void ABaseFighter::MoveHorizontal(float value)
{
    if(Controller && value) 
        AddMovementInput(FVector(0.0f, 1.0f, 0.0f), value);
    
}
void ABaseFighter::MoveJump()
{
    ACharacter::Jump();
}
void ABaseFighter::MoveCrouch()
{
    GetCharacterMovement()->Crouch();
}
void ABaseFighter::MoveDash()
{
    
}
void ABaseFighter::MoveAirDash()
{
    
}

float ABaseFighter::GetHPPercent()
{
    if(fCurrHP<0)
        return 0;
    else
        return (fCurrHP / fMaxHP);
}

