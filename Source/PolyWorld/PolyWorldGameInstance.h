// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PolyWorld.h"
#include "PolyWorldGameInstance.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPlayFabGSDKGameInstance, Log, All);
/**
 * 
 */
UCLASS()
class POLYWORLD_API UPolyWorldGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	virtual void Init() override;

protected:
	virtual void OnStart() override;

	UFUNCTION()
		void OnGSDKShutdown();

	UFUNCTION()
		bool OnGSDKHealthCheck();

	UFUNCTION()
		void OnGSDKServerActive();

	UFUNCTION()
		void OnGSDKReadyForPlayers();

public:
	// Title Data (from Server)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayfabTitleData")
	float PolydustCount = 1.4f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayfabTitleData")
	float BattleDuration = 180.f;

	// Player Info
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	FPlayerInfo PlayerInfo;
	// All Owned Polymons
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	TArray<FPolymonInfo> OwnedPolymons;
	// Backback 6 Polymons
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	TArray<FPolymonInfo> AvailablePolymons;
	// Selected 3 Polymons
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	TArray<FPolymonInfo> SelectedPolymons;
	
	//
	UFUNCTION(BlueprintCallable, Category = "Native")
	FPlayerInfo GetPlayerInfo();
	// SavePlayerData
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Playfab")
	void SavePlayerData();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Playfab")
	void LoadPlayerData();
	//
	UFUNCTION(BlueprintCallable, Category = "Native")
	FPolymonInfo GetSelectedPolymon(int32 Index);
	//
	UFUNCTION(BlueprintCallable, Category = "Native")
	void SetSelectedPolymons(const TArray<FPolymonInfo>& SelectedPolys);
	//
	UFUNCTION(BlueprintCallable, Category = "Native")
	TArray<FPolymonInfo> GetAvailablePolymons();

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Native")
	void SR_GenerateNewPolymonInfo(const FPolymonInfo& polymonTemplate, const FPlayerInfo& Player);
};
