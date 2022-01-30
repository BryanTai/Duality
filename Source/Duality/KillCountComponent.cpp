// Fill out your copyright notice in the Description page of Project Settings.


#include "KillCountComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UKillCountComponent::UKillCountComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;

	// ...

	KillCount = 0;
	CurrentActiveDoorIndex = -1;
}

void UKillCountComponent::AddKillCount()
{
	SetKillCount(KillCount + 1);
}

void UKillCountComponent::SetKillCount(int newCount)
{
	KillCount = newCount;
	UE_LOG(LogConfig, Warning, TEXT("KillCount: %d"), KillCount);
	NotifyListeners();
}

int UKillCountComponent::GetKillCount()
{
	return KillCount;
}

void UKillCountComponent::ResetKillCount()
{
	KillCount = 0;
}


// Called when the game starts
void UKillCountComponent::BeginPlay()
{
	Super::BeginPlay();

	// Find all KillCountListeners and cache them
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AKillCountListener::StaticClass(), Listeners);
	UE_LOG(LogConfig, Warning, TEXT("There are %d KillCountListener(s)"), Listeners.Num());

	UpdateActiveDoor();
	
}

void UKillCountComponent::NotifyListeners()
{
	// for (const auto Listener : Listeners)
	// {
	// 	AKillCountListener* CastListener = Cast<AKillCountListener>(Listener);
	// 	if( CastListener->GetIsActive())
	// 	{
	// 		CastListener->Notify(KillCount);
	// 	}
	// }

	if(CurrentActiveDoor != nullptr && CurrentActiveDoor->GetIsActive())
	{
		bool DoorIsActive = CurrentActiveDoor->Notify(KillCount);
		if(!DoorIsActive)
		{
			UpdateActiveDoor();
			ResetKillCount();
		}
	}
}

void UKillCountComponent::UpdateActiveDoor()
{
	CurrentActiveDoorIndex++;
	
	for (const auto Listener : Listeners)
	{
		AKillCountDoor* Door = Cast<AKillCountDoor>(Listener);
		if(Door->GetDoorIndex() == CurrentActiveDoorIndex)
		{
			CurrentActiveDoor = Door;
			return;
		}
	}

	if(CurrentActiveDoor != nullptr)
	{
		CurrentActiveDoor->ToggleActive(true);
	}
}


// Called every frame
// void UKillCountComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
// {
// 	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
// 	// ...
// }

