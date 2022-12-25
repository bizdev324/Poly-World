// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Polymon.h"
#include "BattleHUD.h"
#include "BattlePC.generated.h"

/**
 * 
 */
UCLASS()
class POLYWORLD_API ABattlePC : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY()
	FTimerHandle timer;

public:
	// Sets default values for this character's properties
	ABattlePC();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UBattleHUD> BattleHUDClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UBattleHUD* BattleHUDRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Opponent")
	ABattlePC* Opponent;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Polymon")
	APolymon* SpawnedPolymon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
	int32 PlayerIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
	int32 SelectedPolymonIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
	TArray<bool> AvailablePolymons = { true,true,true };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
	TArray<float> PolymonsRemainingHealth = { 0.f,0.f,0.f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
	bool bCanPlay = false;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
	int32 WonRounds = 0;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
	FPlayerInfo playerInfo;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Polymon")
	APolymon* GetSpawnedPolymonRef() { return SpawnedPolymon; }

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UI")
	void CL_InitializeUI();
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UI")
	void CL_SetHUDWithPolymon();
	// SetOpponetInfo
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Polymon")
	void SR_SetOpponentInfo(const FPlayerInfo& OpponentInfo, const TArray<FPolymonInfo>& OpponentPolymons);
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Polymon")
	void CL_SetOpponentInfo(const FPlayerInfo& OpponentInfo, const TArray<FPolymonInfo>& OpponentPolymons);

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Msg")
	void CL_PrintMsg(const FString& Msg) const;

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Polymon")
	void CL_SpawnPolymon();
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Polymon")
	void SR_SpawnPolymon(const FPolymonInfo& polyInfo);
	UFUNCTION(BlueprintCallable, Category = "Polymon")
	void SelectedPolymon(int32 Index);
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Polymon")
	void SR_SelectedPolymon(int32 Index);
	// Set PlayerInfo
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Polymon")
	void SR_SetPlayerInfo(const FPlayerInfo& pplayerInfo);
	// Battle TimerOut
	UFUNCTION(Server, Reliable,BlueprintCallable, Category = "Polymon")
	void SR_OnBattleTimerOut();
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Polymon")
	void CL_OnOpponentSelectedPolymon();
	//
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Battle")
	void CL_StartBattle();
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Battle")
	void CL_EndBattle();

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Polymon")
	void CL_UpdatePlayerHealth(float HealthPercentage);
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Polymon")
	void CL_UpdateOpponentHealth(float HealthPercentage);
	UFUNCTION(BlueprintCallable, Category = "Polymon")
	void OnPolymonDeath();
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Polymon")
	void CL_OnPolymonDeath(bool bIsPlayer);
	//
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Polymon")
	void CL_EndRound(bool bIsPlayerWinner);
	//
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Polymon")
	void CL_StartSelecting();

	UFUNCTION(BlueprintCallable, Category = "Polymon")
	void RestartRound();

	UFUNCTION()
	void BindInputActions();

	UFUNCTION(BlueprintCallable, Category = "Polymon")
	void Action1();
	UFUNCTION(BlueprintCallable, Category = "Polymon")
	void Action2();
	UFUNCTION(BlueprintCallable, Category = "Polymon")
	void Action3();
	UFUNCTION(BlueprintCallable, Category = "Polymon")
	void Action4();
	UFUNCTION(BlueprintCallable, Category = "Polymon")
	void Action5();
	UFUNCTION(BlueprintCallable, Category = "Polymon")
	void Action6();
};
