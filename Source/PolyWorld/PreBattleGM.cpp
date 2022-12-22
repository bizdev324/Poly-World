// Fill out your copyright notice in the Description page of Project Settings.


#include "PreBattleGM.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "TimerManager.h"

void APreBattleGM::BeginPlay()
{
	Super::BeginPlay();
	//
	if (Player2 == nullptr)
	{
		GetWorld()->GetTimerManager().SetTimer(ExitTimer, this, &APreBattleGM::StartClosingServer, 60.f, false);
		MC_BroadcastMsg(TEXT("Started Closing Timer"));
	}
}

void APreBattleGM::MC_BroadcastMsg_Implementation(const FString& Msg)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
}

void APreBattleGM::CloseServer()
{
	FGenericPlatformMisc::RequestExit(true);
}

void APreBattleGM::StartClosingServer()
{
	MC_BroadcastMsg(TEXT("Closing Server!"));
	if (Player1)
	{
		Player1->CL_EndBattle();
	}
	if (Player2)
	{
		Player2->CL_EndBattle();
	}
	GetWorld()->GetTimerManager().SetTimer(ExitTimer, this, &APreBattleGM::CloseServer, 3.f, false);
}

void APreBattleGM::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	//
	APreBattlePC* PC = Cast<APreBattlePC>(NewPlayer);
	if (Player1 == nullptr)
	{
		Player1 = PC;
	}
	else
	{
		GetWorldTimerManager().ClearTimer(ExitTimer);
		ExitTimer.Invalidate();
		MC_BroadcastMsg(TEXT("InValidating & Clearing Exit Timer."));
		Player2 = PC;
		PC->Opponent = Player1;
		Player1->Opponent = Player2;
		Player1->CL_ShowHUD();
		Player2->CL_ShowHUD();
	}
}

void APreBattleGM::Logout(AController* Exiting)
{
	if (!bIsTravelling)
	{
		MC_BroadcastMsg(TEXT("Player Quit the game!"));
		StartClosingServer();
	}
}

void APreBattleGM::CheckPlayersReady(bool bIsReady)
{
	
	PlayersReady+= bIsReady? 1 : -1;
	if (PlayersReady >= 2)
	{
		bIsTravelling = true;
		StartBattle();
	}
}

void APreBattleGM::StartBattle_Implementation()
{
	GetWorld()->ServerTravel(BattleMapPath);
}
