// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PreBattlePC.h"
#include "PreBattleGM.generated.h"

/**
 * 
 */
UCLASS()
class POLYWORLD_API APreBattleGM : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Players")
	APreBattlePC* Player1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Players")
	APreBattlePC* Player2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Players")
	int32 PlayersReady = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle")
	FString BattleMapPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle")
	bool bIsTravelling = false;

	UPROPERTY()
	FTimerHandle ExitTimer;
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void MC_BroadcastMsg(const FString& Msg);
	UFUNCTION()
	void StartClosingServer();
	UFUNCTION()
	void CloseServer();

	virtual void Logout(AController* Exiting) override;
protected:

	virtual void BeginPlay() override;
	

	/** Called as part of DispatchPostLogin */
	virtual void OnPostLogin(AController* NewPlayer) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Polymon")
	void StartBattle();
public:
	

	UFUNCTION(BlueprintCallable, Category = "Polymon")
	void CheckPlayersReady(bool bIsReady);
};
