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

void AEnemySpawner::SpawnObject(FVector CurrentLoc, FString EnemyType)
{
	
	FActorSpawnParameters SpawnParams;


	if (EnemyType == "BP_ChaseNPC_C")
	{
		AActor* SpawnedActorRef_1 = GetWorld()->SpawnActor<AActor>(ChaseActor, CurrentLoc, GetActorRotation(), SpawnParams);
		AActor* SpawnedActorRef_2 = GetWorld()->SpawnActor<AActor>(ChaseActor, CurrentLoc, GetActorRotation(), SpawnParams);
	}
	else if (EnemyType == "BP_FlyingNPC_C")
	{
		AActor* SpawnedActorRef_1 = GetWorld()->SpawnActor<AActor>(FlyingActor, CurrentLoc, GetActorRotation(), SpawnParams);
		AActor* SpawnedActorRef_2 = GetWorld()->SpawnActor<AActor>(FlyingActor, CurrentLoc, GetActorRotation(), SpawnParams);
	}
	else if (EnemyType == "BP_JumpNPC_C")
	{
		AActor* SpawnedActorRef_1 = GetWorld()->SpawnActor<AActor>(JumpActor, CurrentLoc, GetActorRotation(), SpawnParams);
		AActor* SpawnedActorRef_2 = GetWorld()->SpawnActor<AActor>(JumpActor, CurrentLoc, GetActorRotation(), SpawnParams);
	}
	else if (EnemyType == "BP_ShootNPC_C")
	{
		AActor* SpawnedActorRef_1 = GetWorld()->SpawnActor<AActor>(ShootActor, CurrentLoc, GetActorRotation(), SpawnParams);
		AActor* SpawnedActorRef_2 = GetWorld()->SpawnActor<AActor>(ShootActor, CurrentLoc, GetActorRotation(), SpawnParams);
	}


	UE_LOG(LogConfig, Warning, TEXT("Spawning %s enemy"), *EnemyType);
	//UEnemyHealth* EnemyHealthComponent = Cast<UEnemyHealth>(SpawnedActorRef->GetComponentByClass(UEnemyHealth::StaticClass()));
	//EnemyHealthComponent->SwapTeam(Team);

}

