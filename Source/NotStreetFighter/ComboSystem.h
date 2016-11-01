// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ComboSystem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NOTSTREETFIGHTER_API UComboSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
    UComboSystem();
    virtual ~UComboSystem();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
    void AddToBuffer(char c);
    char GetPreviousEntry();
    FString CreateComboString();
protected:
    TCircularBuffer<char>* InputBuffer;
    int32 CurrentIndex;
    int32 PreviousIndex; 
    int32 StringFormationStartIndex;
    int32 StringFormationEndIndex;
    FTimerHandle ResetBufferTimer;
    bool bLegalComboFound; 
};
