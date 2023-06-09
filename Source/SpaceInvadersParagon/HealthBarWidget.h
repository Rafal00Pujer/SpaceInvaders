// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADERSPARAGON_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UHealthBarWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	FORCEINLINE void SetHealthBarPercent(float Percent) const;

private:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UProgressBar* HealthBar;
};
