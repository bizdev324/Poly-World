// Fill out your copyright notice in the Description page of Project Settings.


#include "PreBattleHUD.h"
#include "PreBattlePC.h"
#include "PolyWorldGameInstance.h"

void UPreBattleHUD::SetPlayerInfo_Implementation(const FString& PlayerName, const TArray<FPolymonInfo>& PlayerPolymons)
{

}

void UPreBattleHUD::SetOpponentInfo_Implementation(const FString& OpponentName, const TArray<FPolymonInfo>& OpponentPolymons)
{

}

void UPreBattleHUD::SetOpponentReady_Implementation(bool bIsReady)
{

}

void UPreBattleHUD::SetPlayerReady(bool bIsReady)
{
	APreBattlePC* PC = Cast<APreBattlePC>(GetOwningPlayer());
	if (PC != nullptr)
	{
		PC->SR_SetOpponentReady(bIsReady);
	}
}

void UPreBattleHUD::SetSelectedPolymons(const TArray<FPolymonInfo>& SelectedPolys)
{
	UPolyWorldGameInstance* PWGI = Cast<UPolyWorldGameInstance>(GetGameInstance());
	if (PWGI != nullptr)
	{
		PWGI->SetSelectedPolymons(SelectedPolys);
	}
}