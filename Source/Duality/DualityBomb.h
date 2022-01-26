// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DualityBomb.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class DUALITY_API ADualityBomb : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;
	
	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;
	
public:	
	// Sets default values for this actor's properties
	ADualityBomb();

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Bomb)
	int DamageAmount;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
