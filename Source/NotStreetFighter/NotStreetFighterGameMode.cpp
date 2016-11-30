// Fill out your copyright notice in the Description page of Project Settings.

#include "NotStreetFighter.h"
#include "StageCamera.h"
#include "EngineUtils.h" 
#include "NotStreetFighterGameMode.h"

ANotStreetFighterGameMode::ANotStreetFighterGameMode()
{
    bDelayedStart = true;
    P1WinCount = 0;
    P2WinCount = 0;
    MaxTimer = 10   ;
    CurrTimer = MaxTimer;
    MaxRounds = 1;
    CurrRound = 1;
    bShouldCallSuperBeginPlay = false;
}


void ANotStreetFighterGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if(CurrTimer == 0)
    {
        EndMatch();
    }
}

void ANotStreetFighterGameMode::BeginPlay()
{
    //Game Mode Begin Play fire AFTER all the other actors
    if(bShouldCallSuperBeginPlay)
        Super::BeginPlay();
    
    Player1->SetActorLocation(FVector(0.0f, -100.0f, 108.1f));
    Player2->SetActorLocation(FVector(0.0f, 100.0f, 108.1f));
    CurrTimer = MaxTimer;
    Player1->fCurrHP = Player1->fMaxHP;
    Player2->fCurrHP = Player2->fMaxHP;
    Player1->fCurrentSuperGauge = 0.0f;
    Player2->fCurrentSuperGauge = 0.0f;
    
}
void ANotStreetFighterGameMode::StartPlay()
{
    UGameplayStatics::CreatePlayer(GetWorld(), 1);
    Player1 = Cast<ABaseFighter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    Player2 = Cast<ABaseFighter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 1));
    BeginPlay();
    CreateHUD();
    bShouldCallSuperBeginPlay = true;
    if (MatchState == MatchState::EnteringMap)
    {
        SetMatchState(MatchState::WaitingToStart);
    }
    
}

void ANotStreetFighterGameMode::HandleMatchIsWaitingToStart()
{
    for(TActorIterator<AStageCamera> AIt(GetWorld()); AIt; ++AIt)
    {
        AStageCamera* camera = *AIt;
        for(auto It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
        {
            APlayerController* PC = *It;
            PC->SetIgnoreMoveInput(true);
            PC->SetViewTarget(camera); 
        }
        
    }
    CreateRoundWidget();
    FTimerHandle StartMatchTimer;
    GetWorld()->GetTimerManager().SetTimer(StartMatchTimer, this, &ANotStreetFighterGameMode::StartMatch, 4.0f);
    if (GameSession != NULL)
    {
        GameSession->HandleMatchIsWaitingToStart();
    }
    
    
}


void ANotStreetFighterGameMode::StartMatch()
{
    bShouldCallSuperBeginPlay = false;
    if (HasMatchStarted())
    {
        // Already started
        return;
    }
    
    //Let the game session override the StartMatch function, in case it wants to wait for arbitration
    if (GameSession->HandleStartMatchRequest())
    {
        return;
    }
       
            
        
    SetMatchState(MatchState::InProgress);
}

void ANotStreetFighterGameMode::HandleMatchHasStarted()
{
    //super notifies calls the begin play on everybody
    GameSession->HandleMatchHasStarted();
    
    // start human players first
    Super::HandleMatchHasStarted(); 
    //make input active
    for(auto It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PC = *It;
        PC->ResetIgnoreInputFlags();
        
    }
    //GetWorld()->GetTimerManager().SetTimer(CountDownTimer, this, &ANotStreetFighterGameMode::DecrementTimer, 1.0f, true);
    
}

void ANotStreetFighterGameMode::EndMatch()
{
    GetWorld()->GetTimerManager().ClearTimer(CountDownTimer);
    //See if a character won best of X
    //If best of X not finished, reset the match
    
    bool P1Win = P1WinCount == (MaxRounds+1)/2;
    bool P2Win = P2WinCount == (MaxRounds +1)/2;
    bool bGameOver = P1Win || P2Win;
    if(!bGameOver)
    {
        //Reset HP, Positions etc
        SetMatchState(MatchState::WaitingToStart);
        BeginPlay();
        CurrRound++; 
    }
        
    //Sets match state to Waiting Post Match
    else
    {
        if(P1Win)
            bWinner = true;
        else
            bWinner = false;
        SetMatchState(MatchState::WaitingPostMatch);
    }
}

void ANotStreetFighterGameMode::HandleMatchHasEnded()
{
    if(bWinner)
    {
        UE_LOG(LogTemp, Log, TEXT("Player 1 Wins!"));
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Player 2 Wins!"));
    }
    //Calls GameSession to Hadnle same thing
    //Stops Game Instance from recording
    Super::HandleMatchHasEnded();
}

void ANotStreetFighterGameMode::StartToLeaveMap()
{
    SetMatchState(MatchState::LeavingMap);
}

void ANotStreetFighterGameMode::HandleLeavingMap()
{
    ReturnToMainMenuHost();
}



