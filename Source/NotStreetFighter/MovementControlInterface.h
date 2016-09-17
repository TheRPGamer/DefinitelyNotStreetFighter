// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Object.h" 
#include "MovementControlInterface.generated.h"

/**
 * 
 */
UINTERFACE()
class NOTSTREETFIGHTER_API UMovementControlInterface : public UInterface
{
    GENERATED_BODY()
};

class NOTSTREETFIGHTER_API IMovementControlInterface
{
    GENERATED_BODY()
public:
    virtual void MoveHorizontal(float value){}
    virtual void MoveJump(){}
    virtual void MoveCrouch(){}
    virtual void MoveDash(){}
    virtual void MoveAirDash(){}
}; 
