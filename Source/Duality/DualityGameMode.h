// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DualityCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "DualityGameMode.generated.h"

UCLASS(minimalapi)
class ADualityGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

#pragma region HUD
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<class UUserWidget> MainHUDClass;

	UPROPERTY()
	class UUserWidget* ActiveWidget;

	virtual void BeginPlay() override;
#pragma endregion

public:
	// UFUNCTION(BlueprintCallable)
	// ADualityCharacter* GetPlayerDualityCharacter();
	
	ADualityGameMode();
};



