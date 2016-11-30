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
    PlayerAttacksAC = nullptr;
    PlayerVoiceAC = nullptr;
    PlayerThemeAC = nullptr;
    
    GetCharacterMovement()->GravityScale = 2.0f;
    GetCharacterMovement()->GroundFriction = 3.0f;
    GetCharacterMovement()->JumpZVelocity = 400.0f;
    GetCharacterMovement()->MaxWalkSpeed = 200.0f;
    GetCharacterMovement()->AirControl = 0.9f;
    GetCharacterMovement()->bOrientRotationToMovement = false;
    GetCharacterMovement()->bConstrainToPlane = true;
    //This is for LOCAL space, not world space
    GetCharacterMovement()-> SetPlaneConstraintNormal(FVector(1.0f, 0.0f, 0.0f));
    
    
    bMoveHorizontalFirstPoll = true;
    
    ComboSystem = CreateDefaultSubobject<UComboSystem>(TEXT("ComboSystem"));
    
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
    if(value > 0) ComboSystem->b6Held =true;
    if(value < 0) ComboSystem->b4Held = true;
    
    if (value == 0)
    {
        if(ComboSystem->b6Held) ComboSystem->AddComboInputOnRelease(6);
        if(ComboSystem->b4Held) ComboSystem->AddComboInputOnRelease(4);
        ComboSystem->b4Held = false;
        ComboSystem->b6Held = false;
        bMoveHorizontalFirstPoll = true;
        
    }
    
    
    if(Controller && value)
    {
        AddMovementInput(FVector(0.0f, 1.0f, 0.0f), value);
        if(bMoveHorizontalFirstPoll)
        {
            if(value > 0) ComboSystem->AddComboInputOnPress(6);
            if(value < 0) ComboSystem->AddComboInputOnPress(4);
            bMoveHorizontalFirstPoll = false;
        }
    
    }
}
void ABaseFighter::MoveJump()
{
    ACharacter::Jump();
    ComboSystem->b8Held = true;
    ComboSystem->AddComboInputOnPress(8);
    
}
void ABaseFighter::MoveCrouch()
{
    GetCharacterMovement()->Crouch();
    ComboSystem->b2Held = true;
    ComboSystem->AddComboInputOnPress(2);
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

void ABaseFighter::OnJumpRelease()
{
    ComboSystem->AddComboInputOnRelease(8);
    ComboSystem->b8Held = false;
}

void ABaseFighter::OnCrouchRelease()
{
    ComboSystem->AddComboInputOnRelease(2);
    ComboSystem->b2Held = false;
}

void ABaseFighter::LightPunch()
{
    ComboSystem->AddComboInputOnPress('a');
}

void ABaseFighter::MediumPunch()
{
    ComboSystem->AddComboInputOnPress('b');
}
void ABaseFighter::HeavyPunch()
{
    ComboSystem->AddComboInputOnPress('c');
}
void ABaseFighter::LightKick()
{
    ComboSystem->AddComboInputOnPress('x');
}
void ABaseFighter::MediumKick()
{
    ComboSystem->AddComboInputOnPress('y');
}
void ABaseFighter::HeavyKick()
{
    ComboSystem->AddComboInputOnPress('z');
}

UAudioComponent* ABaseFighter::CreateAC(USoundCue* cue)
{
    UAudioComponent* audio = nullptr;
    if(cue)
    {
        audio = UGameplayStatics::SpawnSoundAttached(cue, RootComponent);
    }
    return audio; 
}