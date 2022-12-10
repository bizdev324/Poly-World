// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleGM.h"

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
		Player2 = PC;
		PC->PlayerIndex = 2;
		PC->Opponent = Player1;
		Player1->Opponent = Player2;
	}
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
	Player1->SpawnedPolymon->StartPolydustGenerationTimer(PolydustGenerationRate);
	Player2->SpawnedPolymon->StartPolydustGenerationTimer(PolydustGenerationRate);
	Player1->CL_StartBattle();
	Player2->CL_StartBattle();
}
