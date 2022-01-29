// Fill out your copyright notice in the Description page of Project Settings.


#include "KillCountDoor.h"

#include <string>

// Sets default values
AKillCountDoor::AKillCountDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKillCountDoor::BeginPlay()
{
	Super::BeginPlay();

	//TODO: Get reference to Text component
	if(TextComponent == nullptr)
	{
		TextComponent = Cast<UTextRenderComponent>(GetComponentByClass(UTextRenderComponent::StaticClass()));
	}

	UpdateNumberDisplay(KillCountThreshold);
}

void AKillCountDoor::Notify(int NewKillCount)
{
	Super::Notify(NewKillCount);

	const int KillsRemaining = KillCountThreshold - NewKillCount;
	UpdateNumberDisplay(KillsRemaining);
	
	if(KillsRemaining <= 0)
	{
		//TODO: Open the door
		UE_LOG(LogConfig, Warning, TEXT("DOOR IS OPEN!"));
	}
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



