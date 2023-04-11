// Fill out your copyright notice in the Description page of Project Settings.


#include "SIPCharacter.h"

#include "Components/CapsuleComponent.h"

// Sets default values
ASIPCharacter::ASIPCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void ASIPCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASIPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASIPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASIPCharacter::Fire()
{
	if (!ProjectileType)
	{
		UE_LOG(LogTemp, Warning, TEXT("Projectile Type is null!!"));
		return;
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = this;
	
	GetWorld()->SpawnActor<AActor>(ProjectileType,ProjectileSpawnPoint->GetComponentTransform(),SpawnParameters);

	if (FireMontage)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Fire Montage!!"));
		PlayAnimMontage(FireMontage);
	}
}

void ASIPCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

int32 ASIPCharacter::GetDamageOnCollisionSelf() const
{
	return DamageOnCollisionSelf;
}

int32 ASIPCharacter::GetDamageOnCollisionOther() const
{
	return DamageOnCollisionOther;
}
