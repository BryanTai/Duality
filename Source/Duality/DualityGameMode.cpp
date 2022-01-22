// Copyright Epic Games, Inc. All Rights Reserved.

#include "DualityGameMode.h"
#include "DualityHUD.h"
#include "DualityCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADualityGameMode::ADualityGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ADualityHUD::StaticClass();
}
