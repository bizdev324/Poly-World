// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleHUD.h"

void UBattleHUD::NativeConstruct()
{
    Super::NativeConstruct();
    //

}

void UBattleHUD::StartBattleTimer_Implementation(float Time)
{

}

void UBattleHUD::UpdatePlayerHealth_Implementation(float healthPercentage)
{

}

void UBattleHUD::UpdateOpponentHealth_Implementation(float healthPercentage)
{

}

void UBattleHUD::StartSelecting_Implementation(const TArray<bool>& AvailablePolymons)
{

}

void UBattleHUD::EndRound_Implementation(bool bIsPlayerWon)
{

}

void UBattleHUD::OnOpponentFinishSelecting_Implementation()
{

}

void UBattleHUD::DestroyCapsule_Implementation(bool bIsPlayerCapsule)
{

}

void UBattleHUD::SetHUDwithPolymon_Implementation(ABattlePC* PCRef)
{

}

void UBattleHUD::SetPlayerInfo_Implementation(const FPlayerInfo& PlayerInfo, const TArray<FPolymonInfo>& PlayerPolymons)
{

}

void UBattleHUD::SetOpponentInfo_Implementation(const FPlayerInfo& OpponentInfo, const TArray<FPolymonInfo>& OpponentPolymons)
{

}