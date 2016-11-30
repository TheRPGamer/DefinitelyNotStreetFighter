// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseFighter.h"
#include "NotRyu.generated.h"

/**
 * 
 */
UCLASS()
class NOTSTREETFIGHTER_API ANotRyu : public ABaseFighter
{
	GENERATED_BODY()
public:
    virtual void BeginPlay() override;
protected:
    void Hadouken();
    void Shoryuken();
    void Tatsu();
    void ShinkuHadouken();
    void ProcessComboString(FName combo) override;
	
	
	
};
