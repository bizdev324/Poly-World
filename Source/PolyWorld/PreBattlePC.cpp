// Fill out your copyright notice in the Description page of Project Settings.


#include "PreBattlePC.h"
#include "PolyWorldGameInstance.h"
#include "PreBattleGM.h"

void APreBattlePC::CL_ShowHUD_Implementation()
{
	FInputModeGameAndUI inputMode;
	if (PreBattleHUDClass != nullptr)
	{
		PreBattleHUDRef = Cast<UPreBattleHUD>(CreateWidget(this, PreBattleHUDClass));
		inputMode.SetWidgetToFocus(PreBattleHUDRef->TakeWidget());
		PreBattleHUDRef->AddToViewport();
	}
	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	SetInputMode(inputMode);
	SetShowMouseCursor(true);
	// Setting UI aspects
	UPolyWorldGameInstance* PWGI = Cast<UPolyWorldGameInstance>(GetGameInstance());
	if (PWGI != nullptr)
	{
		PreBattleHUDRef->SetPlayerInfo(PWGI->GetPlayerInfo().Name, PWGI->GetAvailablePolymons());
		SR_SetOpponentInfo(PWGI->GetPlayerInfo().Name, PWGI->GetAvailablePolymons());
	}
}

void APreBattlePC::SR_SetOpponentInfo_Implementation(const FString& PlayerName, const TArray<FPolymonInfo>& PlayerPolymons)
{
	Opponent->CL_SetOpponentInfo(PlayerName, PlayerPolymons);
}

void APreBattlePC::CL_SetOpponentInfo_Implementation(const FString& PlayerName, const TArray<FPolymonInfo>& PlayerPolymons)
{
	PreBattleHUDRef->SetOpponentInfo(PlayerName, PlayerPolymons);
}

void APreBattlePC::SR_SetOpponentReady_Implementation(const bool bIsReady)
{
	Opponent->CL_SetOpponentReady(bIsReady);
	APreBattleGM* GM = GetWorld()->GetAuthGameMode<APreBattleGM>();
	GM->CheckPlayersReady(bIsReady);
}

void APreBattlePC::CL_SetOpponentReady_Implementation(const bool bIsReady)
{
	PreBattleHUDRef->SetOpponentReady(bIsReady);
}