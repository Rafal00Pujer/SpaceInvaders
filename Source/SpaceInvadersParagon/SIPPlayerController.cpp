// Fill out your copyright notice in the Description page of Project Settings.


#include "SIPPlayerController.h"
#include "SIPCharacter.h"
#include "SIPGameMode.h"

void ASIPPlayerController::HandleGameOver()
{
	SetInputsForGameOver();
	FireReleased();
}

void ASIPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputsForPlay();

	GetPawn()->OnEndPlay.AddDynamic(this, &ASIPPlayerController::OnPlayerDestroy);
}

void ASIPPlayerController::SetInputsForPlay()
{
	InputComponent->RemoveActionBinding(FireActionName, IE_Pressed);

	InputComponent->BindAction(FireActionName, IE_Pressed, this, &ASIPPlayerController::FirePressed);
	InputComponent->BindAction(FireActionName, IE_Released, this, &ASIPPlayerController::FireReleased);

	InputComponent->BindAxis(MoveRightAxisName, GetPawn<ASIPCharacter>(), &ASIPCharacter::MoveRight);
}

void ASIPPlayerController::SetInputsForGameOver()
{
	InputComponent->AxisBindings.RemoveAllSwap([AxisName = MoveRightAxisName](const FInputAxisBinding Item)-> bool
	{
		return Item.AxisName == AxisName;
	}, false);

	InputComponent->RemoveActionBinding(FireActionName, IE_Pressed);
	InputComponent->RemoveActionBinding(FireActionName, IE_Released);

	InputComponent->BindAction(FireActionName, IE_Pressed, this, &ASIPPlayerController::PlayAgain);
}

void ASIPPlayerController::FirePressed()
{
	if (!GetPawn())
	{
		// UE_LOG(LogTemp,Warning,TEXT("Player Pawn is null!!"));
		return;
	}

	bFireLoop = true;

	FTimerManager& TimerManager = GetWorldTimerManager();

	if (TimerManager.IsTimerActive(FireLoopTimer))
	{
		return;
	}

	TimerManager.SetTimer(FireLoopTimer, this, &ASIPPlayerController::FireLoop, AttackCooldown, true, 0);
}

void ASIPPlayerController::FireReleased()
{
	bFireLoop = false;
}

void ASIPPlayerController::FireLoop()
{
	if (!bFireLoop || !GetPawn())
	{
		GetWorldTimerManager().ClearTimer(FireLoopTimer);
		return;
	}

	GetPawn<ASIPCharacter>()->Fire();
}

void ASIPPlayerController::PlayAgain()
{
	// SetInputsForPlay();

	RestartLevel();
}

void ASIPPlayerController::OnPlayerDestroy(AActor* Actor, EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetAuthGameMode<ASIPGameMode>()->PlayerDiedNotify();
}
