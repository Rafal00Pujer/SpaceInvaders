// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "EnemyAIController.h"
#include "HealthBarWidget.h"
#include "SIPGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::CreateHealthWidget()
{
	HealthWidget = NewObject<UWidgetComponent>(GetOwner(),TEXT("HealthWidget"));
	HealthWidget->AttachToComponent(GetOwner()->GetRootComponent(),
	                                FAttachmentTransformRules::KeepRelativeTransform);
	HealthWidget->RegisterComponent();
	HealthWidget->SetCollisionProfileName(TEXT("NoCollision"));
	
	HealthWidget->SetWidgetClass(HealthWidgetType);
	HealthWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidget->SetDrawSize(HealthWidgetDrawSize);

	// UE_LOG(LogTemp, Warning, TEXT("Created Health Widget!!"));
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                  AController* InstigatedBy, AActor* DamageCauser)
{
	CurrentHealth -= Damage;
	// UE_LOG(LogTemp, Warning, TEXT("Actor %s current health: %i"), *GetOwner()->GetName(), CurrentHealth);

	if (CurrentHealth <= 0)
	{
		GetOwner()->Destroy();
	}
	else if (HealthWidgetType)
	{
		if (!HealthWidget)
		{
			CreateHealthWidget();
		}

		Cast<UHealthBarWidget, UUserWidget>(HealthWidget->GetWidget())->
			SetHealthBarPercent(static_cast<float>(CurrentHealth) / static_cast<float>(MaxHealth));
	}
}
