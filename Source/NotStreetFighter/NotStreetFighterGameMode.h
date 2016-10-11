// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "BaseFighter.h"
#include "NotStreetFighterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class NOTSTREETFIGHTER_API ANotStreetFighterGameMode : public AGameMode
{
	GENERATED_BODY()
public:
    ANotStreetFighterGameMode();

protected:
    ABaseFighter* Player1;
    ABaseFighter* Player2;
    int32 MaxTimer;
    int32 CurrTimer;
    int32 MaxRounds;
    int32 CurrRound;
    bool bWinner;
    int32 P1WinCount;
    int32 P2WinCount;
    
    FTimerHandle CountDownTimer;
protected:
    void Tick(float DeltaTime) override;
    void BeginPlay() override; 

    UFUNCTION(BlueprintCallable, Category = "Game")
    void StartPlay() override;
    void HandleMatchIsWaitingToStart() override;
    void StartMatch() override;
    void HandleMatchHasStarted() override;
    void EndMatch() override;
    void HandleMatchHasEnded() override;
    void StartToLeaveMap() override;
    
protected:
    void ResetMatch(); 
    FORCEINLINE void CountDown() {--CurrTimer;}
    
public:
    UFUNCTION(exec)
    void Test()
    {
        StartMatch();
        UE_LOG(LogTemp, Log, TEXT("Test")); 
    
    }
    
    UFUNCTION(exec)
    void TestDamage()
    {
        Player1->fCurrHP -= 20; 
    }
    
    FORCEINLINE void DecrementTimer() {--CurrTimer;}
    
    
public:
    UFUNCTION(BlueprintCallable, Category = "HP")
    ABaseFighter* GetPlayer1() {return Player1;}
    
    UFUNCTION(BlueprintCallable, Category = "Super")
    ABaseFighter* GetPlayer2() const {return Player2;}
    
    UFUNCTION(BlueprintCallable, Category = "Timer")
    int32 GetRemainingTime() const {return CurrTimer;}
    
    UFUNCTION(BlueprintCallable, Category = "Rounds")
    int32 GetRoundNumber() const {return CurrRound;}
    
    UFUNCTION(BlueprintImplementableEvent)
    void CreateRoundWidget();

    


    

};
