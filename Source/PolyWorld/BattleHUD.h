// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	void OnOpponentFinishSelecting();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	void DestroyCapsule(bool bIsPlayerCapsule);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	void SetHUDwithPolymon(ABattlePC* PCRef);
};
