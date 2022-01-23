// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Shootable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UShootable : public UInterface
{
	GENERATED_BODY()
};

/**
 *  Represents a class that can be shot by the Player
 */
class DUALITY_API IShootable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// This gets called when the object has been hit with a player projectile
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "OnShot Event")
	void OnShot();
};
