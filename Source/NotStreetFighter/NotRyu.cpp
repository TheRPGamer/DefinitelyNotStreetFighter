// Fill out your copyright notice in the Description page of Project Settings.

#include "NotStreetFighter.h"
#include "NotRyu.h"

void ANotRyu::BeginPlay()
{
    Super::BeginPlay();
    ComboSystem->SetOwner(this); 
}

void ANotRyu::ProcessComboString(FName combo)
{
    if(combo == FName(TEXT("236236c")))
    {
        ShinkuHadouken();
        return;
    }
    if(combo == FName(TEXT("6236a")))
    {
        Shoryuken();
        return;
    }
    if(combo == FName(TEXT("623a")))
    {
        Shoryuken();
        return;
    }
    if(combo == FName(TEXT("236a")))
    {
        Hadouken();
        return;
    }
    if(combo == FName(TEXT("214x")))
    {
        Tatsu();
        return;
    }
    if(combo == FName(TEXT("66")))
    {
        MoveDash();
        return;
    }
    
    
    
}

void ANotRyu::Hadouken()
{
    UE_LOG(LogTemp, Log, TEXT("Hadouken"));
    PlayerVoiceAC = CreateAC(PlayerVoiceSoundArray[0]);
    if(PlayerVoiceAC)
        PlayerVoiceAC->Play();
}
void ANotRyu::Shoryuken()
{
    UE_LOG(LogTemp, Log, TEXT("Shoryuken"));
    PlayerVoiceAC = CreateAC(PlayerVoiceSoundArray[1]);
    if(PlayerVoiceAC)
        PlayerVoiceAC->Play();
}
void ANotRyu::Tatsu()
{
    UE_LOG(LogTemp, Log, TEXT("I'd like some pound cake"));
    PlayerVoiceAC = CreateAC(PlayerVoiceSoundArray[2]);
    if(PlayerVoiceAC)
        PlayerVoiceAC->Play();
}
void ANotRyu::ShinkuHadouken()
{
    UE_LOG(LogTemp, Log, TEXT("SHINKU "));
    PlayerVoiceAC = CreateAC(PlayerVoiceSoundArray[3]);
    if(PlayerVoiceAC)
        PlayerVoiceAC->Play();
}


