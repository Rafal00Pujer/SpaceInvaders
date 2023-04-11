// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainWidget.h"
#include "SIPCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "SIPGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADERSPARAGON_API ASIPGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void PlayerDiedNotify();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASIPCharacter> EnemyType;

	UPROPERTY(EditDefaultsOnly)
	FName EnemiesSpawnZeroPointName;

	UPROPERTY(VisibleAnywhere)
	TArray<ASIPCharacter*> SpawnedEnemies;

	UPROPERTY(EditDefaultsOnly)
	FName EndLevelTriggerName;

	UPROPERTY(EditDefaultsOnly)
	uint32 NumberOfEnemiesInRow = 1;

	UPROPERTY(EditDefaultsOnly)
	uint32 NumberOfRows = 1;

	UPROPERTY(EditDefaultsOnly)
	uint32 DistanceBetweenEnemies = 1;

	UPROPERTY(EditDefaultsOnly)
	uint32 DistanceBetweenRows = 1;

	UPROPERTY(EditDefaultsOnly)
	uint32 ScorePointsPerEnemyKill = 100;

	UPROPERTY(VisibleAnywhere)
	uint32 Score = 0;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainWidget> MainWidgetType;

	UPROPERTY(VisibleAnywhere)
	UMainWidget* MainWidget;

	void SpawnEnemies();

	UFUNCTION()
	void OnEnemyDestroy(AActor* Actor, EEndPlayReason::Type EndPlayReason);

	UFUNCTION()
	void OnEndLevelTriggerOverlap(AActor* OverlappedActor, AActor* OtherActor);

	void CreateMainWidget();

	void AddEndLevelTriggerOverlap();

	void RemoveEnemy(ASIPCharacter* EnemyToRemove);

	void HandleGameOver() const;
};
