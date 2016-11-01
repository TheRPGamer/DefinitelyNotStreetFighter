    // Fill out your copyright notice in the Description page of Project Settings.

#include "NotStreetFighter.h"
#include "ComboSystem.h"
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

