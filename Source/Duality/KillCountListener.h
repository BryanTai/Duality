// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KillCountListener.generated.h"

UCLASS()
class DUALITY_API AKillCountListener : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKillCountListener();

	int GetKillCountThreshold();

	UFUNCTION(BlueprintCallable, Category=KillCount)
	void ToggleActive(bool ToggleActive);
	bool GetIsActive();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=KillCount)
	int KillCountThreshold;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=KillCount)
	bool IsActive;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	virtual void Notify(int NewKillCount);

};
