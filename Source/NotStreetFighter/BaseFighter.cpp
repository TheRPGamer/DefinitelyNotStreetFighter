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
    
    b2Held = false;
    b4Held = false;
    b6Held = false;
    b8Held = false;
    bMoveHorizontalFirstPoll = true;
    
    ComboSystem = CreateDefaultSubobject<UComboSystem>(TEXT("ComboSystem"));
    
    testCounter = 0;
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
    testCounter++;
    if(testCounter == 150)
    {
        FString fstring = ComboSystem->CreateComboString();
        UE_LOG(LogTemp, Log, TEXT("Combo String: %s"), *fstring);
        testCounter = 0;
    }

}

// Called to bind functionality to input
void ABaseFighter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
    InputComponent->BindAxis("MoveRight", this, &ABaseFighter::MoveHorizontal);
    InputComponent->BindAction("Crouch", IE_Pressed, this, &ABaseFighter::MoveCrouch);
    InputComponent->BindAction("Jump", IE_Pressed, this, &ABaseFighter::MoveJump);
    InputComponent->BindAction("JumpRelease", IE_Released, this, &ABaseFighter::OnJumpRelease);
    InputComponent->BindAction("CrouchRelease", IE_Released, this, &ABaseFighter::OnCrouchRelease);
    
    InputComponent->BindAction("LPunch", IE_Pressed, this, &ABaseFighter::LightPunch);
    InputComponent->BindAction("MPunch", IE_Pressed, this, &ABaseFighter::MediumPunch);
    InputComponent->BindAction("HPunch", IE_Pressed, this, &ABaseFighter::HeavyPunch);
    InputComponent->BindAction("LKick", IE_Pressed, this, &ABaseFighter::LightKick);
    InputComponent->BindAction("MKick", IE_Pressed, this, &ABaseFighter::MediumKick);
    InputComponent->BindAction("HKick", IE_Pressed, this, &ABaseFighter::HeavyKick);
}
/*
 * READ READ READ READ READ READ READ READ READ 
 * The inputs into the Combosystem follow this pattern 
 * 789  8 is up
 * 456  4 is left 6 is right
 * 123  2 is down
 */
void ABaseFighter::MoveHorizontal(float value)
{
    if(value > 0) b6Held =true;
    if(value < 0) b4Held = true;
    if (value == 0)
    {
        if(b6Held) AddComboInputOnRelease(6);
        if(b4Held) AddComboInputOnRelease(4);
        b4Held = false;
        b6Held = false;
        bMoveHorizontalFirstPoll = true;
        
    }
    
    
    if(Controller && value)
    {
        AddMovementInput(FVector(0.0f, 1.0f, 0.0f), value);
        if(bMoveHorizontalFirstPoll)
        {
            if(value > 0) AddComboInputOnPress(6);
            if(value < 0) AddComboInputOnPress(4);
            bMoveHorizontalFirstPoll = false;
        }
    
    }
}
void ABaseFighter::MoveJump()
{
    ACharacter::Jump();
    b8Held = true;
    AddComboInputOnPress(8);
    
}
void ABaseFighter::MoveCrouch()
{
    GetCharacterMovement()->Crouch();
    b2Held = true;
    AddComboInputOnPress(2);
}
void ABaseFighter::MoveDash()
{
    
}
void ABaseFighter::MoveAirDash()
{
    
}

float ABaseFighter::GetHPPercent()
{
    if(fCurrHP < 0.0f)
        fCurrHP = 0.0f;
    
    return (fCurrHP / fMaxHP);
}

void ABaseFighter::AddComboInputOnPress(char c)
{
    switch((int32)c)
    {
        case 2:
        {
            if(b4Held)
                ComboSystem->AddToBuffer(1);
            else if(b6Held)
                ComboSystem->AddToBuffer(3);
            else
                ComboSystem->AddToBuffer(2);
            break;
        }
        case 6:
        {
            if(b2Held)
                ComboSystem->AddToBuffer(3);
            else if(b8Held)
                ComboSystem->AddToBuffer(9);
            else
                ComboSystem->AddToBuffer(6);
            break;
        }
            
        case 8:
        {
            if(b6Held)
                ComboSystem->AddToBuffer(9);
            else if(b4Held)
                ComboSystem->AddToBuffer(7);
            else
                ComboSystem->AddToBuffer(8);
            break;
        }
            
        case 4:
        {
            if(b8Held)
                ComboSystem->AddToBuffer(7);
            else if(b2Held)
                ComboSystem->AddToBuffer(1);
            else
                ComboSystem->AddToBuffer(4);
            break;
        }
        default:
        {
            ComboSystem->AddToBuffer(c);
            break; 
        }
    }
}

void ABaseFighter::AddComboInputOnRelease(char c)
{
    
    switch((int32)c)
    {
        case 2:
        {
            if(b4Held)
                ComboSystem->AddToBuffer(4);
            if(b6Held)
                ComboSystem->AddToBuffer(6);
            break;
        }
        case 6:
        {
            if(b2Held)
                ComboSystem->AddToBuffer(2);
            if(b8Held)
                ComboSystem->AddToBuffer(8);
            break;
        }
                
        case 8:
        {
            if(b6Held)
                ComboSystem->AddToBuffer(6);
            if(b4Held)
                ComboSystem->AddToBuffer(4);
            break;
        }
                
        case 4:
        {
            if(b8Held)
                ComboSystem->AddToBuffer(8);
            if(b2Held)
                ComboSystem->AddToBuffer(2);
            break;
                
        }
    }
}

void ABaseFighter::OnJumpRelease()
{
    AddComboInputOnRelease(8);
    b8Held = false;
}

void ABaseFighter::OnCrouchRelease()
{
    AddComboInputOnRelease(2);
    b2Held = false;
}

void ABaseFighter::LightPunch()
{
    AddComboInputOnPress('a');
}

void ABaseFighter::MediumPunch()
{
    AddComboInputOnPress('b');
}
void ABaseFighter::HeavyPunch()
{
    AddComboInputOnPress('c');
}
void ABaseFighter::LightKick()
{
    AddComboInputOnPress('x');
}
void ABaseFighter::MediumKick()
{
    AddComboInputOnPress('y');
}
void ABaseFighter::HeavyKick()
{
    AddComboInputOnPress('z');
}
