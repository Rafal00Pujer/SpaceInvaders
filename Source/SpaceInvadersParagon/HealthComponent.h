// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"
#include "HealthComponent.generated.h"


class UHealthBarWidget;
UCLASS(ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent))
class SPACEINVADERSPARAGON_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	int32 MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	int32 CurrentHealth;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UHealthBarWidget> HealthWidgetType;

	UPROPERTY(EditDefaultsOnly)
	FVector2D HealthWidgetDrawSize;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* HealthWidget;

	void CreateHealthWidget();
	
	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	                class AController* InstigatedBy, AActor* DamageCauser);
};
