// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHealth.h"
#include "EnemySpawner.h"
#include "Kismet/GameplayStatics.h"

#include "DualityGameMode.h"
#include "KillCountComponent.h"

// Sets default values for this component's properties
UEnemyHealth::UEnemyHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;

	// ...

	StartingHealth = 3;

}

void UEnemyHealth::OnHitEvent(int DamageTaken)
{
	CurrentHealth -= DamageTaken;

	if(CurrentHealth <= 0)
	{
		TriggerDeath();
	}
	else
	{
		TriggerDamage();
	}
}

void UEnemyHealth::TriggerDeath()
{
	UKillCountComponent* KillCounter = static_cast<UKillCountComponent*>(GetWorld()->GetAuthGameMode()->
		GetComponentByClass(UKillCountComponent::StaticClass()));
	
	AActor* ParentActor = GetOwner();
	UE_LOG(LogConfig, Warning, TEXT("Enemy %s destroyed!"), *ParentActor->GetName());

	KillCounter->AddKillCount();

	ParentActor->Destroy();

	TArray<AActor*> ActorsToFind;
	if (UWorld* World = GetWorld())
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), ActorsToFind);
	}
	for (AActor* EnemySpawnerActor : ActorsToFind)

	{
		//Is this Actor of type Enemyspawner class?
		AEnemySpawner* EnemySpawnerCast = Cast<AEnemySpawner>(EnemySpawnerActor);
		if (EnemySpawnerCast)
		{
			FTimerDelegate TimerDel;
			FTimerHandle TimerHandle;
			TimerDel.BindUFunction(EnemySpawnerCast, FName("SpawnObject"), GetOwner()->GetActorLocation(), ParentActor->GetClass()->GetName());
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 5.f, false);
			
		}
	}

}

void UEnemyHealth::TriggerDamage()
{
	const AActor* ParentActor = Cast<AActor>(GetOwner());
	UE_LOG(LogConfig, Warning, TEXT("Hit %s! Health is %d"), *ParentActor->GetName(), CurrentHealth);
}


// Called when the game starts
void UEnemyHealth::BeginPlay()
{
	Super::BeginPlay();

	// ...
	CurrentHealth = StartingHealth;
}


// Called every frame
// void UEnemyHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
// {
// 	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
// 	// ...
// }

