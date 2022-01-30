// Fill out your copyright notice in the Description page of Project Settings.


#include "KillCountDoor.h"

#include <string>

// Sets default values
AKillCountDoor::AKillCountDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	DoorIndex = 0;
}

int AKillCountDoor::GetDoorIndex()
{
	return DoorIndex;
}

// Called when the game starts or when spawned
void AKillCountDoor::BeginPlay()
{
	Super::BeginPlay();
	
	if(TextComponent == nullptr)
	{
		TextComponent = Cast<UTextRenderComponent>(GetComponentByClass(UTextRenderComponent::StaticClass()));
	}

	UpdateNumberDisplay(KillCountThreshold);
}

bool AKillCountDoor::Notify(int NewKillCount)
{
	const bool HasHitThreshold = Super::Notify(NewKillCount);

	const int KillsRemaining = KillCountThreshold - NewKillCount;
	UpdateNumberDisplay(KillsRemaining);
	
	if(KillsRemaining <= 0)
	{
		//TODO: Open the door
		UE_LOG(LogConfig, Warning, TEXT("DOOR IS OPEN!"));
		TriggerOpenDoor();
	}

	return HasHitThreshold;
}

void AKillCountDoor::UpdateNumberDisplay(int NumberToDisplay) const
{
	TextComponent->SetText(FText::AsNumber(NumberToDisplay));
}

// Called every frame
// void AKillCountDoor::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
//
// }



