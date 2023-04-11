// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"

UHealthBarWidget::UHealthBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UHealthBarWidget::SetHealthBarPercent(float Percent) const
{
	HealthBar->SetPercent(Percent);
}
