    // Fill out your copyright notice in the Description page of Project Settings.

#include "NotStreetFighter.h"
#include "ComboSystem.h"
#include "BaseFighter.h" 
#include "Runtime/Core/Public/Misc/Char.h"
#include <string>



// Sets default values for this component's properties
UComboSystem::UComboSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
    InputBuffer = new TCircularBuffer<char>(15);
    CurrentIndex = 0;
    PreviousIndex = InputBuffer->Capacity()-1;
    StringFormationStartIndex = 0;
    StringFormationEndIndex = 0;
    
    b2Held = false;
    b4Held = false;
    b6Held = false;
    b8Held = false;
}

UComboSystem::~UComboSystem()
{
    delete InputBuffer;
}

// Called when the game starts
void UComboSystem::BeginPlay()
{
	Super::BeginPlay();
    // ...
	
}


// Called every frame
void UComboSystem::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UComboSystem::AddToBuffer(char c)
{
    (*InputBuffer)[CurrentIndex] = c;
    PreviousIndex = CurrentIndex;
    CurrentIndex = InputBuffer->GetNextIndex(CurrentIndex);
    StringFormationEndIndex = InputBuffer->GetNextIndex(StringFormationEndIndex);
    
}
char UComboSystem::GetPreviousEntry()
{
    return (*InputBuffer)[PreviousIndex];
}
FString UComboSystem::CreateComboString()
{
    FString input;
    int32 i = StringFormationStartIndex;
    while(i != StringFormationEndIndex)
    {
        char temp = (*InputBuffer)[i];
        if((int) temp < 10)
        {
            UE_LOG(LogTemp, Log, TEXT("Current index: %i"), i);
            int32 num = (int32)temp;
            UE_LOG(LogTemp, Log, TEXT("Number Cast: %i"), num);
            input.AppendInt(num);
        }
        else
        {
            std::string str;
            str += temp;
            input += FString(str.c_str());
            
        }
        i = InputBuffer->GetNextIndex(i);
    }
    StringFormationStartIndex = StringFormationEndIndex;
    return input;
}


void UComboSystem::AddComboInputOnPress(char c)
{
    
    GetWorld()->GetTimerManager().SetTimer(ResetBufferTimer, this, &UComboSystem::ResetBuffer, 0.3f);

    switch((int32)c)
    {
        case 2:
        {
            if(b4Held)
                AddToBuffer(1);
            else if(b6Held)
                AddToBuffer(3);
            else
                AddToBuffer(2);
            break;
        }
        case 6:
        {
            if(b2Held)
                AddToBuffer(3);
            else if(b8Held)
                AddToBuffer(9);
            else
                AddToBuffer(6);
            break;
        }
            
        case 8:
        {
            if(b6Held)
                AddToBuffer(9);
            else if(b4Held)
                AddToBuffer(7);
            else
                AddToBuffer(8);
            break;
        }
            
        case 4:
        {
            if(b8Held)
                AddToBuffer(7);
            else if(b2Held)
                AddToBuffer(1);
            else
                AddToBuffer(4);
            break;
        }
        default:
        {
            AddToBuffer(c);
            break;
        }
    }
}

void UComboSystem::AddComboInputOnRelease(char c)
{
    
    GetWorld()->GetTimerManager().SetTimer(ResetBufferTimer, this, &UComboSystem::ResetBuffer, 0.3f);

    switch((int32)c)
    {
        case 2:
        {
            if(b4Held)
                AddToBuffer(4);
            if(b6Held)
                AddToBuffer(6);
            break;
        }
        case 6:
        {
            if(b2Held)
                AddToBuffer(2);
            if(b8Held)
                AddToBuffer(8);
            break;
        }
            
        case 8:
        {
            if(b6Held)
                AddToBuffer(6);
            if(b4Held)
                AddToBuffer(4);
            break;
        }
            
        case 4:
        {
            if(b8Held)
                AddToBuffer(8);
            if(b2Held)
                AddToBuffer(2);
            break;
            
        }
    }
}

void UComboSystem::ResetBuffer()
{
    FString combo = CreateComboString();
    UE_LOG(LogTemp, Log, TEXT("Combo String: %s"), *combo);
    Owner->ProcessComboString(FName(*combo));
    StringFormationStartIndex = StringFormationEndIndex;
    GetWorld()->GetTimerManager().ClearTimer(ResetBufferTimer); 
}

