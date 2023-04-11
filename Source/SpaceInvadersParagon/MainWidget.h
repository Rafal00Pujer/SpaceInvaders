// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADERSPARAGON_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UMainWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void SetScoreText(uint32 ScoreValue) const;

	void ShowGameOverScreen() const;

	void HideGameOverScreen() const;

private:
	UPROPERTY(EditDefaultsOnly)
	FString ScoreText;

	UPROPERTY(EditDefaultsOnly)
	FString GameOverScoreText;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UTextBlock* ScoreTextBlock;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UTextBlock* GameOverScoreTextBlock;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UVerticalBox* GameOverVerticalBox;
};
