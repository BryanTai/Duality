// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHealth.h"

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

void UPlayerHealth::OnHit(AActor* OtherActor)
{
	if(IsInvincible)
	{
		UE_LOG(LogConfig, Warning, TEXT("IsInvincible is TRUE, hit IGNORED"));
		return;
	}
	
	UE_LOG(LogConfig, Warning, TEXT("Player has been HIT by %s"), *OtherActor->GetName());

	UEnemyDamage* EnemyDamageComponent = Cast<UEnemyDamage>(OtherActor->GetComponentByClass(UEnemyDamage::StaticClass()));

	if(EnemyDamageComponent != nullptr)
	{
		const int DamageTaken = EnemyDamageComponent->GetEnemyDamageAmount();
		CurrentHealth -= DamageTaken;
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
	}
}

void UPlayerHealth::DisableInvincibility()
{
	IsInvincible = false;
	UE_LOG(LogConfig, Warning, TEXT("IsInvincible DISABLED"));
}


// Called every frame
// void UPlayerHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
// {
// 	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
// 	// ...
// }

