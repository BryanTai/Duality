// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHealth.h"

#include "EnemyDamage.h"
#include "EnemyHealth.h"

// Sets default values for this component's properties
UPlayerHealth::UPlayerHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;

	// ...
	MaxHealth = 3;
	InvincibilityOnDamageSeconds = 3;
}


// Called when the game starts
void UPlayerHealth::BeginPlay()
{
	Super::BeginPlay();

	CapsuleCollider = Cast<UCapsuleComponent>( GetOwner()->GetComponentByClass(UCapsuleComponent::StaticClass()));

	CurrentHealth = MaxHealth;
}

void UPlayerHealth::OnHit(AActor* OtherActor)
{
	//TODO
	UE_LOG(LogConfig, Warning, TEXT("Player has been HIT by %s"), *OtherActor->GetName());

	UEnemyDamage* EnemyDamageComponent = Cast<UEnemyDamage>(OtherActor->GetComponentByClass(UEnemyDamage::StaticClass()));

	if(EnemyDamageComponent != nullptr)
	{
		int DamageTaken = EnemyDamageComponent->GetEnemyDamageAmount();
		//TODO: Message the GameMode!
		//TODO: GO invincible for a bit!
	}
}

void UPlayerHealth::OnOverlap(AActor* OtherActor)
{
	//TODO
	UE_LOG(LogConfig, Warning, TEXT("Player has COLLIDED with %s"), *OtherActor->GetName());
}


// Called every frame
// void UPlayerHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
// {
// 	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
// 	// ...
// }

