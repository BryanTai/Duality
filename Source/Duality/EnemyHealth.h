// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyHealth.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUALITY_API UEnemyHealth : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyHealth();

	UFUNCTION(BlueprintCallable)
	void OnHitEvent(int DamageTaken);

	UFUNCTION(BlueprintCallable)
	void TriggerDeath();

	UFUNCTION(BlueprintCallable)
	void TriggerDamage();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Health)
	int StartingHealth;

	UPROPERTY(VisibleAnywhere, Category=Health)
	int CurrentHealth;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
