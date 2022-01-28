// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	void AddKillCount();
	void SetKillCount(int newCount);
	int GetKillCount();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	int KillCount;

	TArray<AActor*> Listeners;

private:	
	void NotifyListeners();
		
};
