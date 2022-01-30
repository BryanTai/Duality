// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DualityCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class ADualityCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* FP_MuzzleLocation;

	/** Gun mesh: VR view (attached to the VR controller directly, no arm, just the actual gun) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* VR_Gun;

	/** Location on VR gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* VR_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Motion controller (right hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMotionControllerComponent* R_MotionController;

	/** Motion controller (left hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMotionControllerComponent* L_MotionController;

public:
	ADualityCharacter();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ADualityProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ADualityBomb> BombClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 bUsingMotionControllers : 1;

#pragma region GUN

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gun)
	float ProjectileFireVolumeMultiplier;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gun)
	float BombFireVolumeMultiplier;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gun)
	float RapidFireDelay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
	float HeatGainedOnShot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
	float HeatGainedOnBomb;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
	float HeatDecayTime;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
	float RegularHeatDecayAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
	float OverheatLimitAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gun)
	float OverheatDecayAmount;
	
	UPROPERTY(VisibleAnywhere, Category = Gun)
	float CurrentHeatLevel;
	
	UPROPERTY(VisibleAnywhere, Category = Gun)
	float CurrentHeatDecayAmount;

	UFUNCTION(BlueprintCallable, Category = Gun)
	void UpdateCurrentHeatLevel(float Amount);
	
	UFUNCTION(BlueprintPure, Category = Gun)
	float GetCurrentHeatLevel() const;
	
	UFUNCTION(BlueprintPure, Category = Gun)
	float GetOverheatLimitAmount() const;

	UFUNCTION(BlueprintPure, Category = Gun)
	bool GetIsOverheated() const;
	
	bool IsOverheated;

	UFUNCTION(BlueprintPure)
	UUserWidget* GetActiveWidgetHUD();

	UFUNCTION(BlueprintImplementableEvent)
	void OnOverheatTrigger();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnOverheatReset();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeath();
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<class UUserWidget> MainHUDClass;

	UPROPERTY()
	class UUserWidget* ActiveWidget;

	void StartRapidFire();

	void EndRapidFire();

	void StartHeatDecay();
	void HeatDecayEvent();
	
	void OnFire();

	void OnBomb();

	FTimerHandle RapidFireTimerHandle;
	
	FTimerHandle HeatDecayTimerHandle;

private:
	/** Fires a projectile. */
	void ShootProjectile();

	

#pragma endregion
protected:
	UFUNCTION(BlueprintCallable)
	int GetCurrentHealth();


	
	/** Resets HMD orientation and position in VR. */
	void OnResetVR();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;

	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

