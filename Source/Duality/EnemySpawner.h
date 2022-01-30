// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyHealth.h"
#include "EnemySpawner.generated.h"

UCLASS()
class DUALITY_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AActor> ChaseActor;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AActor> FlyingActor;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AActor> JumpActor;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AActor> ShootActor;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	class UCapsuleComponent* CapsuleComponent;

	UFUNCTION()
	void SpawnObject(FVector CurrentLoc, FString EnemyType );


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
