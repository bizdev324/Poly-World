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
	void SetPlayerInfo(const FString& PlayerName, const TArray<FPolymonInfo>& PlayerPolymons);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	void SetOpponentInfo(const FString& OpponentName, const TArray<FPolymonInfo>& OpponentPolymons);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	void SetOpponentReady(bool bIsReady);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetPlayerReady(bool bIsReady);

};
