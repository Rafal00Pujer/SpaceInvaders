// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "SIPCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimerForNextTick(this, &AEnemyAIController::DelayedBeginPlay);
	GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &AEnemyAIController::OnMoveComplete);
}

void AEnemyAIController::DelayedBeginPlay()
{
	GetCharacter()->GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AEnemyAIController::OnCapsuleHit);
	HandleMovement();
	PrepareAttack();
}

void AEnemyAIController::AddLocationOffset(FVector& Location) const
{
	// ReSharper disable once CppDefaultCaseNotHandledInSwitchStatement
	switch (CurrentMoveDirection)
	{
	case MoveLeft:
		Location.Y += MoveLeftDistance;
		break;
	case MoveDown:
		Location.X -= MoveUpDown;
		break;
	case MoveRight:
		Location.Y -= MoveLeftDistance;
		break;
	}
}

void AEnemyAIController::HandleMovement()
{
	FVector CurrentPawnLocation = GetPawn()->GetActorLocation();
	AddLocationOffset(CurrentPawnLocation);
	MoveToLocation(CurrentPawnLocation, -1, false, false);
}

void AEnemyAIController::OnMoveComplete(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	CurrentMoveDirection = TEnumAsByte<MoveDirection>(FMath::Wrap(static_cast<int32>(CurrentMoveDirection) + 1, -1, 2));

	HandleMovement();
}

void AEnemyAIController::OnCapsuleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ASIPCharacter* SIPCharacter = GetPawn<ASIPCharacter>();

	OtherActor->TakeDamage(SIPCharacter->GetDamageOnCollisionOther(), FDamageEvent(), this, SIPCharacter);
	GetPawn()->TakeDamage(SIPCharacter->GetDamageOnCollisionSelf(), FDamageEvent(), this, SIPCharacter);
}

void AEnemyAIController::PrepareAttack()
{
	FVector TraceStart = GetPawn()->GetActorLocation();
	FVector TraceEnd = TraceStart;
	TraceEnd.X -= AttackCheckDistance;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetPawn());
	// CollisionQueryParams.TraceTag = TEXT("TraceTag");
	// GetWorld()->DebugDrawTraceTag = TEXT("TraceTag");

	FHitResult HitResult;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Camera, CollisionQueryParams)
		&& HitResult.GetActor()->GetInstigatorController<AEnemyAIController>())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Hit!!!"));

		HitResult.GetActor()->OnEndPlay.AddDynamic(this, &AEnemyAIController::OnBlockingEnemyDestroy);
		return;
	}

	GetWorldTimerManager().SetTimer(AttackTimer, GetPawn<ASIPCharacter>(), &ASIPCharacter::Fire,
	                                FMath::RandRange(AttackCooldownLowValue, AttackCooldownHighValue), true);
}

void AEnemyAIController::OnBlockingEnemyDestroy(AActor* Actor, EEndPlayReason::Type EndPlayReason)
{
	PrepareAttack();
}
