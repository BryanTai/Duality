// Fill out your copyright notice in the Description page of Project Settings.


#include "KillCountListener.h"

// Sets default values
AKillCountListener::AKillCountListener()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	KillCountThreshold = 10;
	IsActive = false;

}

int AKillCountListener::GetKillCountThreshold()
{
	return KillCountThreshold;
}

void AKillCountListener::ToggleActive(bool ToggleActive)
{
	IsActive = ToggleActive;
}

bool AKillCountListener::GetIsActive()
{
	return IsActive;
}

// Called when the game starts or when spawned
void AKillCountListener::BeginPlay()
{
	Super::BeginPlay();
	
}

void AKillCountListener::Notify(int NewKillCount)
{
	if(NewKillCount >= KillCountThreshold)
	{
		ToggleActive(false);
	}
}

// Called every frame
// void AKillCountListener::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
//
// }

