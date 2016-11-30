// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MovementControlInterface.h"
#include "ComboSystem.h" 
#include "Sound/SoundCue.h" 
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
protected:
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
    UFUNCTION(BlueprintCallable, Category = "SoundCues")
    USoundCue* GetCharacterTheme() {return CharacterThemeSound;}
    virtual void ProcessComboString(FName combo){}

public:
    UPROPERTY(transient)
    UAudioComponent* PlayerVoiceAC;
    UPROPERTY(transient)
    UAudioComponent* PlayerAttacksAC;
    UPROPERTY(transient)
    UAudioComponent* PlayerThemeAC;
protected:
    UPROPERTY(EditDefaultsOnly, Category = "SoundCues")
    USoundCue* CharacterThemeSound;
    UPROPERTY(EditDefaultsOnly, Category = "SoundCues")
    TArray<USoundCue*> PlayerVoiceSoundArray;
    UPROPERTY(EditDefaultsOnly, Category = "SoundCues")
    TArray<USoundCue*> PlayerAttacksSoundArray;
    
protected:
    UAudioComponent* CreateAC(USoundCue* cue); 
protected:
    UComboSystem* ComboSystem;
private:
    bool bMoveHorizontalFirstPoll;
private:
    void OnJumpRelease();
    void OnCrouchRelease();
    
    
};


