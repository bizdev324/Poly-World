// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PreBattleHUD.generated.h"

/**
 * 
 */
UCLASS()
class POLYWORLD_API UPreBattleHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	void SetAvailablePolymonsImages();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	void SetOpponentPolymonsImages(const TArray<FPolymonInfo>& OpponentPolymons);

};
