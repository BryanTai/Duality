// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHealth.h"

#include "DualityCharacter.h"
#include "EnemyDamage.h"

// Sets default values for this component's properties
UPlayerHealth::UPlayerHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;

	// ...
	MaxHealth = 3;
	IsInvincible = false;
	IsDead = false;
}

int UPlayerHealth::GetCurrentHealth()
{
	return CurrentHealth;
}


// Called when the game starts
void UPlayerHealth::BeginPlay()
{
	Super::BeginPlay();

	CapsuleCollider = Cast<UCapsuleComponent>( GetOwner()->GetComponentByClass(UCapsuleComponent::StaticClass()));

	CurrentHealth = MaxHealth;
	InvincibilityDurationSeconds = 3.0f;
}

// Returns true if the player takes damage
bool UPlayerHealth::OnHit(AActor* OtherActor)
{
	if(IsInvincible)
	{
		return false;
	}
	
	//UE_LOG(LogConfig, Warning, TEXT("Player has been HIT by %s"), *OtherActor->GetName());

	UEnemyDamage* EnemyDamageComponent = Cast<UEnemyDamage>(OtherActor->GetComponentByClass(UEnemyDamage::StaticClass()));

	if(EnemyDamageComponent != nullptr)
	{
		if(CurrentHealth > 0)
		{
			TriggerDamage();
			return true;
		}

		TriggerDeath();
	}

	return false;
}

void UPlayerHealth::DisableInvincibility()
{
	IsInvincible = false;
}

void UPlayerHealth::TriggerDamage()
{
	CurrentHealth--;
	UE_LOG(LogConfig, Warning, TEXT("Player takes damage! Current Health is now %d"), CurrentHealth);
	IsInvincible = true;

	FTimerHandle InvincibilityTimerHandle;

	GetWorld()->GetTimerManager().SetTimer(
		InvincibilityTimerHandle,
		this,
		&UPlayerHealth::DisableInvincibility,
		InvincibilityDurationSeconds,
		false,
		InvincibilityDurationSeconds
		);
	//TODO: Flash some UI stuff
}

void UPlayerHealth::TriggerDeath()
{
	//TODO: Game Over!
	if (IsDead) {return;}
	UE_LOG(LogConfig, Warning, TEXT("Player is DEAD!"));

	ADualityCharacter* PlayerCharacter = Cast<ADualityCharacter>( GetOwner());
	PlayerCharacter->OnDeath();
	IsDead = true;
}


// Called every frame
// void UPlayerHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
// {
// 	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
// 	// ...
// }

