// Fill out your copyright notice in the Description page of Project Settings.


#include "PreBattleGM.h"
#include "Kismet/KismetSystemLibrary.h"

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
		Player1->CL_ShowHUD();
		Player2->CL_ShowHUD();
	}
}

void APreBattleGM::CheckPlayersReady(bool bIsReady)
{
	
	PlayersReady+= bIsReady? 1 : -1;
	if (PlayersReady >= 2)
	{
		StartBattle();
	}
}

void APreBattleGM::StartBattle_Implementation()
{
	GetWorld()->ServerTravel(BattleMapPath);
}
