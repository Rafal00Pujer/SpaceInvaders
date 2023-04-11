// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "Projectile.h"
#include "GameFramework/Character.h"
#include "SIPCharacter.generated.h"

UCLASS()
class SPACEINVADERSPARAGON_API ASIPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASIPCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Fire();

	void MoveRight(float AxisValue);

	FORCEINLINE int32 GetDamageOnCollisionSelf() const;
	
	FORCEINLINE int32 GetDamageOnCollisionOther() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(VisibleAnywhere)
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile> ProjectileType;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* FireMontage;

	UPROPERTY(EditDefaultsOnly)
	int32 DamageOnCollisionSelf = 10;
	
	UPROPERTY(EditDefaultsOnly)
	int32 DamageOnCollisionOther = 10;
};
