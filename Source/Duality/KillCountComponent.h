// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KillCountDoor.h"
#include "KillCountListener.h"
#include "Components/SceneComponent.h"
#include "KillCountComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUALITY_API UKillCountComponent : public USceneComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UKillCountComponent();

	UFUNCTION(BlueprintCallable)
	void AddKillCount();
	UFUNCTION(BlueprintCallable)
	void SetKillCount(int newCount);
	UFUNCTION(BlueprintPure)
	int GetKillCount();
	UFUNCTION(BlueprintCallable)
	void ResetKillCount();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	int KillCount;

	TArray<AActor*> Listeners;
	AKillCountDoor* CurrentActiveDoor;
	int CurrentActiveDoorIndex;

private:	
	void NotifyListeners();
	void UpdateActiveDoor();
		
};
