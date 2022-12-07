// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PreBattleHUD.h"
#include "PreBattlePC.generated.h"

/**
 * 
 */
UCLASS()
class POLYWORLD_API APreBattlePC : public APlayerController
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	APreBattlePC* Opponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	TSubclassOf<UPreBattleHUD> PreBattleHUDClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	UPreBattleHUD* PreBattleHUDRef;

	//
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Polymon")
	void CL_ShowHUD();

	// SetOpponetInfo
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Polymon")
	void SR_SetOpponentInfo(const FString& PlayerName, const TArray<FPolymonInfo>& PlayerPolymons);
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Polymon")
	void CL_SetOpponentInfo(const FString& PlayerName, const TArray<FPolymonInfo>& PlayerPolymons);
	// SetOpponetReady
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Polymon")
	void SR_SetOpponentReady(const bool bIsReady);
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Polymon")
	void CL_SetOpponentReady(const bool bIsReady);
};
