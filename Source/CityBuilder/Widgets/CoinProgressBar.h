// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "CoinProgressBar.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDER_API UCoinProgressBar : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Service")
	void UpdateCountCoins();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Service")
	void SetTextMaxCountCoins(const FText &InText);

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CountCoin_Text;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* Production_ProgressBar;
};
