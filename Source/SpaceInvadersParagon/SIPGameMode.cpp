// Fill out your copyright notice in the Description page of Project Settings.


#include "SIPGameMode.h"
#include "EngineUtils.h"
#include "SIPPlayerController.h"
#include "Engine/TriggerBox.h"

void ASIPGameMode::BeginPlay()
{
	Super::BeginPlay();

	CreateMainWidget();
	AddEndLevelTriggerOverlap();
	SpawnEnemies();
}

void ASIPGameMode::PlayerDiedNotify()
{
	for (ASIPCharacter* Enemy : SpawnedEnemies)
	{
		Enemy->OnEndPlay.RemoveDynamic(this, &ASIPGameMode::OnEnemyDestroy);
		Enemy->Destroy();
	}

	SpawnedEnemies.Empty(NumberOfRows * NumberOfEnemiesInRow);

	HandleGameOver();
}

void ASIPGameMode::SpawnEnemies()
{
	if (!EnemyType)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy Type is null!!"));
		return;
	}

	FVector EnemiesSpawnZeroPoint;

	for (TActorIterator<AActor> Iterator(GetWorld()); Iterator; ++Iterator)
	{
		if (Iterator->GetFName() == EnemiesSpawnZeroPointName)
		{
			EnemiesSpawnZeroPoint = Iterator->GetActorLocation();
			break;
		}
	}

	SpawnedEnemies.Reserve(NumberOfRows * NumberOfEnemiesInRow);

	for (uint32 i = 0; i < NumberOfRows; i++)
	{
		FVector EnemiesSpawnRowZeroPoint = EnemiesSpawnZeroPoint;

		for (uint32 j = 0; j < NumberOfEnemiesInRow; ++j)
		{
			ASIPCharacter* Enemy = GetWorld()->SpawnActor<ASIPCharacter>(EnemyType, EnemiesSpawnRowZeroPoint,
			                                                             FRotator(0.0, 180.0, 0.0));
			Enemy->OnEndPlay.AddDynamic(this, &ASIPGameMode::OnEnemyDestroy);

			SpawnedEnemies.Add(Enemy);
			EnemiesSpawnRowZeroPoint.Y += DistanceBetweenEnemies;
		}

		EnemiesSpawnZeroPoint.X -= DistanceBetweenRows;
	}
}

void ASIPGameMode::OnEnemyDestroy(AActor* Actor, EEndPlayReason::Type EndPlayReason)
{
	Score += ScorePointsPerEnemyKill;
	//UE_LOG(LogTemp, Warning, TEXT("Current Score: %i"), Score);

	RemoveEnemy(Cast<ASIPCharacter, AActor>(Actor));

	if (!MainWidget)
	{
		return;
	}

	MainWidget->SetScoreText(Score);
}

void ASIPGameMode::OnEndLevelTriggerOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!OtherActor->IsA<ASIPCharacter>())
	{
		return;
	}

	OtherActor->OnEndPlay.RemoveDynamic(this, &ASIPGameMode::OnEnemyDestroy);
	OtherActor->Destroy();

	RemoveEnemy(Cast<ASIPCharacter, AActor>(OtherActor));
}

void ASIPGameMode::CreateMainWidget()
{
	if (!MainWidgetType)
	{
		UE_LOG(LogTemp, Warning, TEXT("Main Widget Type is null!!!"));
		return;
	}

	MainWidget = CreateWidget<UMainWidget>(GetWorld(), MainWidgetType);
	MainWidget->AddToViewport();
}

void ASIPGameMode::AddEndLevelTriggerOverlap()
{
	for (TActorIterator<ATriggerBox> Iterator(GetWorld()); Iterator; ++Iterator)
	{
		if (Iterator->GetFName() == EndLevelTriggerName)
		{
			Iterator->OnActorBeginOverlap.AddDynamic(this, &ASIPGameMode::OnEndLevelTriggerOverlap);
			return;;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("End Level Trigger not found!!!"));
}

void ASIPGameMode::RemoveEnemy(ASIPCharacter* EnemyToRemove)
{
	SpawnedEnemies.Remove(EnemyToRemove);

	if (SpawnedEnemies.Num() == 0)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Game Over!!"));

		HandleGameOver();
	}
}

void ASIPGameMode::HandleGameOver() const
{
	if (MainWidget)
	{
		MainWidget->ShowGameOverScreen();
	}

	ASIPPlayerController* PlayerController = GetWorld()->GetFirstPlayerController<ASIPPlayerController>();
	
	if (PlayerController)
	{
		PlayerController->HandleGameOver();
	}
}
