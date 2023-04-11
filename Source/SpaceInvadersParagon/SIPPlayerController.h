// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SIPPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADERSPARAGON_API ASIPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void HandleGameOver();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	float AttackCooldown = 1;

	UPROPERTY(VisibleAnywhere)
	bool bFireLoop = false;

	FTimerHandle FireLoopTimer;

	UPROPERTY(EditDefaultsOnly)
	FName FireActionName = "Fire";

	UPROPERTY(EditDefaultsOnly)
	FName MoveRightAxisName = "MoveRight";

	void SetInputsForPlay();

	void SetInputsForGameOver();

	void FirePressed();

	void FireReleased();

	void FireLoop();

	void PlayAgain();

	UFUNCTION()
	void OnPlayerDestroy(AActor* Actor, EEndPlayReason::Type EndPlayReason);
};
