// Fill out your copyright notice in the Description page of Project Settings.


#include "KillCountDoor.h"

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
	
}

void AKillCountDoor::TriggerKillCountEvent()
{
	Super::TriggerKillCountEvent();

	//TODO: Open the door
	UE_LOG(LogConfig, Warning, TEXT("DOOR IS OPEN!"));
}

// Called every frame
// void AKillCountDoor::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
//
// }



