// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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
};
