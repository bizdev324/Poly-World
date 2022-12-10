// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattlePC.h"
#include "BattleGM.generated.h"

/**
 * 
 */
UCLASS()
class POLYWORLD_API ABattleGM : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Players")
	ABattlePC* Player1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Players")
	ABattlePC* Player2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Players")
	int32 PlayersReady = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Players")
	float PolydustGenerationRate = 2.8f;

	
protected:
	/** Called as part of DispatchPostLogin */
	virtual void OnPostLogin(AController* NewPlayer) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Polymon")
	void StartBattle();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Polymon")
	void SpawnPlayers();

public:
	UFUNCTION(BlueprintCallable, Category = "Polymon")
	void CheckPlayersReady();



};
