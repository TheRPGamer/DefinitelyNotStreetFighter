// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MovementControlInterface.h"
#include "ComboSystem.h" 
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
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats")
    float fCurrHP;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStats")
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
    
    
    
    protected:
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
    virtual void LightPunch() override;
    virtual void MediumPunch() override;
    virtual void HeavyPunch() override;
    virtual void LightKick() override;
    virtual void MediumKick() override;
    virtual void HeavyKick() override;
    
public:
    UFUNCTION(BlueprintCallable, Category = "HP")
    float GetHPPercent();
    
    UFUNCTION(BlueprintCallable, Category = "Super")
    float GetSuperPercent() {return (fCurrentSuperGauge / 100.0);}
public:
    UComboSystem* ComboSystem;
    
protected:
    bool b2Held;
    bool b4Held;
    bool b6Held;
    bool b8Held;
    bool bMoveHorizontalFirstPoll;
protected:
    void AddComboInputOnPress(char c);
    void AddComboInputOnRelease(char c);
    void OnJumpRelease();
    void OnCrouchRelease();
    
    int testCounter;
    
};


