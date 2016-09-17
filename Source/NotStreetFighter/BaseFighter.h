// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MovementControlInterface.h"
#include "BaseFighter.generated.h"

UCLASS()
class NOTSTREETFIGHTER_API ABaseFighter : public ACharacter, public IMovementControlInterface
{
	GENERATED_BODY()

public:
	ABaseFighter();

	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CharacterStats")
    float fMaxHP;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CharacterStats")
    float fCurrHP;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CharacterStats")
    float fCurrentSuperGauge;
    
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CharacterStats")
    int32 iJumpCounter;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CharacterStats")
    int32 iAirdashCounter;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CharacterStats")
    int32 iDashCounter;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CharacterStats")
    float fWalkSpeed;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CharacterStats")
    float fDashSpeed;
    
public:
    bool bIsBlockingHigh;
    bool bIsBlockingLow;
    bool bIsInAir;
    bool bIsInBlockStun;
    int32 iJumpLimit;
    int32 iDashLimit;
    int32 iAirDashLimit;
public:
    virtual void MoveHorizontal(float value) override;
    virtual void MoveJump()override;
    virtual void MoveCrouch()override;
    virtual void MoveDash()override;
    virtual void MoveAirDash()override;
    

	
	
};
