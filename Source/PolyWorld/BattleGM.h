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

	UPROPERTY()
	FTimerHandle ExitTimer;

	UFUNCTION()
	void StartClosingServer();
	UFUNCTION()
	void CloseServer();
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void MC_BroadcastMsg(const FString& Msg);

	virtual void Logout(AController* Exiting) override;

protected:
	virtual void BeginPlay() override;

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
