// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */

UENUM()
enum MoveDirection
{
	MoveLeft,
	MoveDown,
	MoveRight
};

UCLASS()
class SPACEINVADERSPARAGON_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	float MoveLeftDistance = 320;

	UPROPERTY(EditDefaultsOnly)
	float MoveUpDown = 300;

	UPROPERTY(EditDefaultsOnly)
	float AttackCooldownLowValue = 1;

	UPROPERTY(EditDefaultsOnly)
	float AttackCooldownHighValue = 10;

	UPROPERTY(EditDefaultsOnly)
	float AttackCheckDistance = 1000;

	UPROPERTY(VisibleAnywhere)
	TEnumAsByte<MoveDirection> CurrentMoveDirection = MoveLeft;

	FTimerHandle AttackTimer;

	void DelayedBeginPlay();

	void AddLocationOffset(FVector& Location) const;

	void HandleMovement();

	void OnMoveComplete(FAIRequestID RequestID, const FPathFollowingResult& Result);

	UFUNCTION()
	void OnCapsuleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                  FVector NormalImpulse, const FHitResult& Hit);

	void PrepareAttack();

	UFUNCTION()
	void OnBlockingEnemyDestroy(AActor* Actor , EEndPlayReason::Type EndPlayReason);
};
