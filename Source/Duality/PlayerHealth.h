// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/CapsuleComponent.h"
#include "PlayerHealth.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUALITY_API UPlayerHealth : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Health)
	int MaxHealth;
	
	UPROPERTY(VisibleAnywhere, Category=Health)
	int CurrentHealth;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Health)
	int InvincibilityOnDamageSeconds;

	UPROPERTY(VisibleDefaultsOnly, Category=Collider)
	UCapsuleComponent* CapsuleCollider;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void OnHit(AActor* OtherActor);
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* OtherActor);
};
