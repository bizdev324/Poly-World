// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PolyWorld.h"
#include "PolyWorldGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class POLYWORLD_API UPolyWorldGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
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
