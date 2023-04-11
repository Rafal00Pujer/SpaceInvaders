// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"

UMainWidget::UMainWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameOverVerticalBox->SetVisibility(ESlateVisibility::Hidden);
}

void UMainWidget::SetScoreText(uint32 ScoreValue) const
{
	ScoreTextBlock->SetText(FText::FromString(ScoreText + FString::FromInt(ScoreValue)));
	GameOverScoreTextBlock->SetText(FText::FromString(GameOverScoreText + FString::FromInt(ScoreValue)));
}

void UMainWidget::ShowGameOverScreen() const
{
	GameOverVerticalBox->SetVisibility(ESlateVisibility::Visible);
	ScoreTextBlock->SetVisibility(ESlateVisibility::Hidden);
}

void UMainWidget::HideGameOverScreen() const
{
	GameOverVerticalBox->SetVisibility(ESlateVisibility::Hidden);
	ScoreTextBlock->SetVisibility(ESlateVisibility::Visible);
}
