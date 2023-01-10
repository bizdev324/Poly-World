// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PolyWorld.h"
#include "BattleHUD.generated.h"

/**
 * 
 */
UCLASS()
class POLYWORLD_API UBattleHUD : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	FTimerHandle BattleTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	TArray<FActionInfo> ActionList;
	//
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	void StartBattleTimer(float Time);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	void UpdatePlayerHealth(float healthPercentage);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	void UpdateOpponentHealth(float healthPercentage);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	void StartSelecting(const TArray<bool> &AvailablePolymons);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	void EndRound(bool bIsPlayerWon);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	void OnOpponentFinishSelecting();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	void DestroyCapsule(bool bIsPlayerCapsule);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	void SetHUDwithPolymon(ABattlePC* PCRef);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	void SetPlayerInfo(const FPlayerInfo& PlayerInfo, const TArray<FPolymonInfo>& PlayerPolymons);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	void SetOpponentInfo(const FPlayerInfo& OpponentInfo, const TArray<FPolymonInfo>& OpponentPolymons);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	void SetActionButtons(const TArray<FActionInfo>& newActionList);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	FActionInfo UseAction(int32 Index);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	FActionInfo GetActionByIndex(int32 Index);
};
