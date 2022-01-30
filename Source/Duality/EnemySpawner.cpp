// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = CapsuleComponent;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnObject(FVector CurrentLoc, int Team)
{
	FVector NewLocation;
	if (Team == 0)
	{
		NewLocation = FVector((CurrentLoc.X + 10860),CurrentLoc.Y,CurrentLoc.Z);
	}
	else
	{
		NewLocation = FVector((CurrentLoc.X - 10860), CurrentLoc.Y,CurrentLoc.Z);
	}
	FActorSpawnParameters SpawnParams;
	AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(ActorToSpawn, NewLocation, GetActorRotation(), SpawnParams);
	
	UEnemyHealth* EnemyHealthComponent = Cast<UEnemyHealth>(SpawnedActorRef->GetComponentByClass(UEnemyHealth::StaticClass()));
	EnemyHealthComponent->SwapTeam(Team);

}

