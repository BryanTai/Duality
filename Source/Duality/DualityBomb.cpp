// Fill out your copyright notice in the Description page of Project Settings.


#include "DualityBomb.h"

#include "EnemyHealth.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ADualityBomb::ADualityBomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;


	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(60.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 6000.f;
	ProjectileMovement->MaxSpeed = 6000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void ADualityBomb::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADualityBomb::OnHit(AActor* OtherActor)
{
	if ((OtherActor != nullptr) && (OtherActor != this))
	{
		TArray<UEnemyHealth*> EnemyHealthComponents;
		OtherActor->GetComponents(EnemyHealthComponents);
		if(EnemyHealthComponents.Num() > 0)
		{
			UEnemyHealth* EnemyHealth = EnemyHealthComponents[0];
			EnemyHealth->OnHitEvent(DamageAmount);
		}
	}
}

void ADualityBomb::ApplyOnHitToActorsInRadius(TArray<AActor*> OtherActors)
{
	UE_LOG(LogConfig, Warning, TEXT("APPLYING HIT TO ALL ACTORS!! Other Actors: %d"), OtherActors.Num());
	
	for (auto OtherActor : OtherActors)
	{
		OnHit(OtherActor);
	}
}

// Called every frame
// void ADualityBomb::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
//
// }

