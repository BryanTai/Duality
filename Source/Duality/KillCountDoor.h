// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KillCountListener.h"
#include "Components/TextRenderComponent.h"
#include "KillCountDoor.generated.h"

UCLASS()
class DUALITY_API AKillCountDoor : public AKillCountListener
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKillCountDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=KillCount)
	UTextRenderComponent* TextComponent;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	virtual void Notify(int NewKillCount) override;

private:
	void UpdateNumberDisplay(int NumberToDisplay) const;

};
