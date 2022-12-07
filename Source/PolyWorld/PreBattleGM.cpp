// Fill out your copyright notice in the Description page of Project Settings.


#include "PreBattleGM.h"

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
		Player2 = PC;
		PC->Opponent = Player1;
		Player1->Opponent = Player2;
	}
}

void APreBattleGM::CheckPlayersReady()
{
	PlayersReady++;
	if (PlayersReady >= 2)
	{

	}
}

void APreBattleGM::StartBattle_Implementation()
{

}
