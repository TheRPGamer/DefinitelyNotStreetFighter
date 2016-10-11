// Fill out your copyright notice in the Description page of Project Settings.

#include "NotStreetFighter.h"
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
    UE_LOG(LogTemp, Log, TEXT("Begin Play.")); 
    //Game Mode Begin Play fire AFTER all the other actors
    Super::BeginPlay();
    auto It = GetWorld()->GetPlayerControllerIterator();
    if(It)
        Player1= Cast<ABaseFighter>((*It)->GetPawn());
    ++It;
    if(It)
        Player2 = Cast<ABaseFighter>((*It)->GetPawn());
    
}
void ANotStreetFighterGameMode::StartPlay()
{
    UE_LOG(LogTemp, Log, TEXT("Start Play"));
    if (MatchState == MatchState::EnteringMap)
    {
        SetMatchState(MatchState::WaitingToStart);
    }
    
}

void ANotStreetFighterGameMode::HandleMatchIsWaitingToStart()
{
    UE_LOG(LogTemp, Log, TEXT("Handle Match Waiting To Start"));
    CreateRoundWidget();
    FTimerHandle StartMatchTimer;
    GetWorld()->GetTimerManager().SetTimer(StartMatchTimer, this, &ANotStreetFighterGameMode::StartMatch, 2.0f);
    if (GameSession != NULL)
    {
        GameSession->HandleMatchIsWaitingToStart();
    }
    GetWorldSettings()->NotifyBeginPlay();
    for(auto It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PC = *It;
        PC->SetIgnoreMoveInput(true); 
    }
    
}


void ANotStreetFighterGameMode::StartMatch()
{
    UE_LOG(LogTemp, Log, TEXT("Start Matdh"));
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
    UE_LOG(LogTemp, Log, TEXT("Handle Match Has Started."));
    //super notifies calls the begin play on everybody
    GameSession->HandleMatchHasStarted();
    
    // start human players first
    for( FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator )
    {
        APlayerController* PlayerController = *Iterator;
        if ((PlayerController->GetPawn() == NULL) && PlayerCanRestart(PlayerController))
        {
            RestartPlayer(PlayerController);
        }
    }
    
    // Make sure level streaming is up to date before triggering NotifyMatchStarted
    GEngine->BlockTillLevelStreamingCompleted(GetWorld());
    
    
    // Then fire off match started
    GetWorldSettings()->NotifyMatchStarted();
    
    // if passed in bug info, send player to right location
    const FString BugLocString = UGameplayStatics::ParseOption(OptionsString, TEXT("BugLoc"));
    const FString BugRotString = UGameplayStatics::ParseOption(OptionsString, TEXT("BugRot"));
    if( !BugLocString.IsEmpty() || !BugRotString.IsEmpty() )
    {
        for( FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator )
        {
            APlayerController* PlayerController = *Iterator;
            if( PlayerController->CheatManager != NULL )
            {
                PlayerController->CheatManager->BugItGoString( BugLocString, BugRotString );
            }
        }
    }
    
    if (IsHandlingReplays() && GetGameInstance() != nullptr)
    {
        GetGameInstance()->StartRecordingReplay(GetWorld()->GetMapName(), GetWorld()->GetMapName());
    }
    //make input active
    for(auto It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PC = *It;
        PC->ResetIgnoreInputFlags();
        if(PC->InputEnabled())
        {
            UE_LOG(LogTemp, Log, TEXT("Input is enabled"));
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("Input NOT enabled"));
        }
    }
    GetWorld()->GetTimerManager().SetTimer(CountDownTimer, this, &ANotStreetFighterGameMode::DecrementTimer, 1.0f, true);
    
}

void ANotStreetFighterGameMode::EndMatch()
{
    UE_LOG(LogTemp, Log, TEXT("End Match"));
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
        ResetMatch();
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
    UE_LOG(LogTemp, Log, TEXT("Handle Match Has End3d."));
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

void AGameMode::HandleLeavingMap()
{
    UE_LOG(LogTemp, Log, TEXT("Handle Leaving Map")); 
    ReturnToMainMenuHost();
}

void ANotStreetFighterGameMode::ResetMatch()
{
    //TODO Reset Position, HP, Timer etc
    CurrTimer = 99;
    Player1->fCurrHP = Player1->fMaxHP;
    //Player2->fCurrHP = Player2->fMaxHP;
    Player1->fCurrentSuperGauge = 0.0f;
    //Player2->fCurrentSuperGauge = 0.0f;
}



