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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	FPlayerInfo PlayerInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	TArray<FPolymonInfo> AvailablePolymons;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	TArray<FPolymonInfo> SelectedPolymons;

	FPolymonInfo GetSelectedPolymon(int32 Index);
};
