// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleGM.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "PolyWorldGameInstance.h"
#include "TimerManager.h"

void ABattleGM::BeginPlay()
{
	Super::BeginPlay();
	//
	if (Player2 == nullptr)
	{
		GetWorld()->GetTimerManager().SetTimer(ExitTimer, this, &ABattleGM::StartClosingServer, 60.f, false);
		MC_BroadcastMsg(TEXT("Started Closing Timer"));
	}
}

void ABattleGM::MC_BroadcastMsg_Implementation(const FString& Msg)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
}

void ABattleGM::CloseServer()
{
	FGenericPlatformMisc::RequestExit(true);
}

void ABattleGM::StartClosingServer()
{
	MC_BroadcastMsg(TEXT("Closing Server"));
	if (Player1)
	{
		Player1->CL_EndBattle();
	}
	if (Player2)
	{
		Player2->CL_EndBattle();
	}
	GetWorld()->GetTimerManager().SetTimer(ExitTimer, this, &ABattleGM::CloseServer, 3.f, false);
}

void ABattleGM::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	//
	ABattlePC* PC = Cast<ABattlePC>(NewPlayer);
	if (Player1 == nullptr)
	{
		Player1 = PC;
		PC->PlayerIndex = 1;
	}
	else
	{
		GetWorldTimerManager().ClearTimer(ExitTimer);
		ExitTimer.Invalidate();
		MC_BroadcastMsg(TEXT("InValidating & Clearing Exit Timer."));
		Player2 = PC;
		PC->PlayerIndex = 2;
		PC->Opponent = Player1;
		Player1->Opponent = Player2;
	}

}

void ABattleGM::Logout(AController* Exiting)
{
	MC_BroadcastMsg(TEXT("Player Exiting"));
	StartClosingServer();
}

void ABattleGM::CheckPlayersReady()
{
	PlayersReady++;
	if (PlayersReady >= 2)
	{
		SpawnPlayers();
		PlayersReady = 0;
	}
}

void ABattleGM::SpawnPlayers_Implementation()
{
	Player1->CL_SpawnPolymon();
	Player2->CL_SpawnPolymon();
}

void ABattleGM::StartBattle_Implementation()
{
	UPolyWorldGameInstance* PWGI = Cast<UPolyWorldGameInstance>(GetGameInstance());
	if (PWGI != nullptr)
	{
		Player1->SpawnedPolymon->StartPolydustGenerationTimer(PWGI->PolydustCount);
		Player2->SpawnedPolymon->StartPolydustGenerationTimer(PWGI->PolydustCount);
		Player1->CL_StartBattle(PWGI->BattleDuration);
		Player2->CL_StartBattle(PWGI->BattleDuration);
	}
}