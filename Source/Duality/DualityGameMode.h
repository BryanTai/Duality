// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
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

	UFUNCTION(BlueprintImplementableEvent, Category=MyImage)
	UImage* GetMyImage() const;
#pragma endregion

	virtual void BeginPlay() override;

public:
	ADualityGameMode();
};



