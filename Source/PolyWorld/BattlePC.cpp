// Fill out your copyright notice in the Description page of Project Settings.


#include "BattlePC.h"
#include "PolyWorldGameInstance.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "EngineUtils.h"
#include "BattleGM.h"

ABattlePC::ABattlePC()
{
	SetReplicates(true);
}

void ABattlePC::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//
	DOREPLIFETIME(ABattlePC, SpawnedPolymon);
}

void ABattlePC::CL_InitializeUI_Implementation()
{
	FInputModeGameAndUI inputMode;
	if (BattleHUDClass != nullptr)
	{
		BattleHUDRef = Cast<UBattleHUD> (CreateWidget(this, BattleHUDClass));
		inputMode.SetWidgetToFocus(BattleHUDRef->TakeWidget());
		BattleHUDRef->AddToViewport();
	}
	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	SetInputMode(inputMode);
	SetShowMouseCursor(true);
	// Setting UI aspects
}

void ABattlePC::CL_SetHUDWithPolymon_Implementation()
{
	BattleHUDRef->SetHUDwithPolymon(this);
}

void ABattlePC::BeginPlay()
{
	Super::BeginPlay();
	//
	if (IsLocalPlayerController())
	{
		BindInputActions();
		CL_InitializeUI();
		UPolyWorldGameInstance* PWGI = Cast<UPolyWorldGameInstance>(GetGameInstance());
		if (PWGI != nullptr)
		{
			for (int i = 0; i < PolymonsRemainingHealth.Num(); i++)
			{
				PolymonsRemainingHealth[i] = PWGI->GetSelectedPolymon(i).Health;
			}
		}
	}
}

void ABattlePC::BindInputActions()
{
	InputComponent->BindAction("Action1", IE_Pressed, this, &ABattlePC::Action1);
	InputComponent->BindAction("Action2", IE_Pressed, this, &ABattlePC::Action2);
	InputComponent->BindAction("Action3", IE_Pressed, this, &ABattlePC::Action3);
	InputComponent->BindAction("Action4", IE_Pressed, this, &ABattlePC::Action4);
	InputComponent->BindAction("Action5", IE_Pressed, this, &ABattlePC::Action5);
	InputComponent->BindAction("Action6", IE_Pressed, this, &ABattlePC::Action6);
}

void ABattlePC::CL_UpdatePlayerHealth_Implementation(float HealthPercentage)
{
	BattleHUDRef->UpdatePlayerHealth(HealthPercentage);
}

void ABattlePC::CL_UpdateOpponentHealth_Implementation(float HealthPercentage)
{
	BattleHUDRef->UpdateOpponentHealth(HealthPercentage);

}

void ABattlePC::SelectedPolymon(int32 Index)
{
	SelectedPolymonIndex = Index;
	SR_SelectedPolymon(Index);
}

void ABattlePC::SR_SelectedPolymon_Implementation(int32 Index)
{
	SelectedPolymonIndex = Index;
	Opponent->CL_OnOpponentSelectedPolymon();
	ABattleGM* GM = GetWorld()->GetAuthGameMode<ABattleGM>();
	GM->CheckPlayersReady();
}

void ABattlePC::CL_OnOpponentSelectedPolymon_Implementation()
{
	BattleHUDRef->OnOpponentFinishSelecting();
}

void ABattlePC::CL_SpawnPolymon_Implementation()
{
	UPolyWorldGameInstance* PWGI = Cast<UPolyWorldGameInstance>(GetGameInstance());
	if (PWGI != nullptr)
	{
		SR_SpawnPolymon(PWGI->GetSelectedPolymon(SelectedPolymonIndex));
		SR_SetPlayerInfo(PWGI->GetPlayerInfo());
	}
}

void ABattlePC::SR_SetPlayerInfo_Implementation(const FPlayerInfo& pplayerInfo)
{
	this->playerInfo = pplayerInfo;
}

void ABattlePC::SR_SpawnPolymon_Implementation(const FPolymonInfo& polyInfo)
{
	FTransform spawnTransform = FTransform();
	TArray<AActor*> OutPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(),OUT OutPoints);
	FString index = FString::FromInt(PlayerIndex);
	FName IndexName = FName(*index);
	FActorSpawnParameters params;
	params.Owner = this;
	for (AActor* actor : OutPoints)
	{
		APlayerStart* point = Cast<APlayerStart>(actor);
		if (point->PlayerStartTag == IndexName)
		{
			spawnTransform = point->GetTransform();
		}
	}
	SpawnedPolymon = GetWorld()->SpawnActorDeferred<APolymon>(APolymon::StaticClass(), spawnTransform, this);
	SpawnedPolymon->PolymonInfo = polyInfo;
	SpawnedPolymon->CurrentHealth = PolymonsRemainingHealth[SelectedPolymonIndex] == 0.f ? polyInfo.Health : PolymonsRemainingHealth[SelectedPolymonIndex];
	SpawnedPolymon->MC_SetModel();
	SpawnedPolymon->OwnerPC = this;
	Possess(SpawnedPolymon);
	SpawnedPolymon->FinishSpawning(spawnTransform);
}

void ABattlePC::CL_StartBattle_Implementation()
{
	BattleHUDRef->StartBattleTimer(180.f);
}

void ABattlePC::Action1()
{
	if (SpawnedPolymon != nullptr)
	{
		SpawnedPolymon->SR_StartAction(0);
	}
}
void ABattlePC::Action2()
{
	if (SpawnedPolymon != nullptr)
	{
		SpawnedPolymon->SR_StartAction(1);
	}
}
void ABattlePC::Action3()
{
	if (SpawnedPolymon != nullptr)
	{
		SpawnedPolymon->SR_StartAction(2);
	}
}
void ABattlePC::Action4()
{
	if (SpawnedPolymon != nullptr)
	{
		SpawnedPolymon->SR_StartAction(3);
	}
}
void ABattlePC::Action5()
{
	if (SpawnedPolymon != nullptr)
	{
		SpawnedPolymon->SR_StartAction(4);
	}
}
void ABattlePC::Action6()
{
	if (SpawnedPolymon != nullptr)
	{
		SpawnedPolymon->SR_StartAction(5);
	}
}

void ABattlePC::OnPolymonDeath()
{
	// Save Opponent Polymon Remaining Health & Increase Won Rounds
	Opponent->PolymonsRemainingHealth[Opponent->SelectedPolymonIndex] = Opponent->SpawnedPolymon->CurrentHealth;
	Opponent->WonRounds++;
	CL_OnPolymonDeath(true);
	Opponent->CL_OnPolymonDeath(false);
	if (Opponent->WonRounds >= 3)
	{
		// Update Score 
		Opponent->playerInfo.RankingPoints = Opponent->playerInfo.RankingPoints + 28;
		int32 playerPoints = playerInfo.RankingPoints - 28;
		playerInfo.RankingPoints = playerPoints < 0 ? 0 : playerPoints;
		// Battle Ended
		FTimerHandle timer;
		FTimerDelegate TDelegate;
		TDelegate.BindUFunction(this, FName("ClientTravel"), TEXT("MainMenuMap"), ETravelType::TRAVEL_Absolute);
		GetWorldTimerManager().SetTimer(timer, TDelegate, 3.f, false);
	}
	else
	{
		// Round Ended
		FTimerHandle timer;
		GetWorldTimerManager().SetTimer(timer, this, &ABattlePC::RestartRound, 3.f, false);
	}
}

void ABattlePC::RestartRound()
{
	SpawnedPolymon->Destroy();
	Opponent->SpawnedPolymon->Destroy();
	CL_StartSelecting();
	Opponent->CL_StartSelecting();
}

void ABattlePC::CL_OnPolymonDeath_Implementation(bool bIsPlayerDeath)
{
	if (bIsPlayerDeath)
	{
		AvailablePolymons[SelectedPolymonIndex] = false;
	}
	BattleHUDRef->DestroyCapsule(bIsPlayerDeath);
	CL_EndRound(!bIsPlayerDeath);
}

void ABattlePC::CL_EndRound_Implementation(bool bIsPlayerWinner)
{
	BattleHUDRef->EndRound(bIsPlayerWinner);
}

void ABattlePC::SR_OnBattleTimerOut_Implementation()
{
	if (SpawnedPolymon->bCanPlay)
	{
		// Disable Action
		SpawnedPolymon->bCanPlay = false;
		Opponent->SpawnedPolymon->bCanPlay = false;
		// Save Polymons Remaining Health
		Opponent->PolymonsRemainingHealth[Opponent->SelectedPolymonIndex] = Opponent->SpawnedPolymon->CurrentHealth;
		PolymonsRemainingHealth[SelectedPolymonIndex] = SpawnedPolymon->CurrentHealth;
		// Decide Winner for the Round
		if (SpawnedPolymon->CurrentHealth > Opponent->SpawnedPolymon->CurrentHealth)
		{
			WonRounds++;
			CL_EndRound(true);
			Opponent->CL_EndRound(false);
		}
		else
		{
			Opponent->WonRounds++;
			CL_EndRound(false);
			Opponent->CL_EndRound(true);
		}
		// 
		if (WonRounds >= 3)
		{
			playerInfo.RankingPoints = playerInfo.RankingPoints + 28;
			int32 OpponentPoints = Opponent->playerInfo.RankingPoints - 28;
			Opponent->playerInfo.RankingPoints = OpponentPoints < 0 ? 0 : OpponentPoints;
			// Battle Ended
			FTimerHandle timer;
			FTimerDelegate TDelegate;
			TDelegate.BindUFunction(this, FName("ClientTravel"), TEXT("MainMenuMap"), ETravelType::TRAVEL_Absolute);
			GetWorldTimerManager().SetTimer(timer, TDelegate, 3.f, false);
		}
		else if (Opponent->WonRounds >= 3)
		{
			Opponent->playerInfo.RankingPoints = Opponent->playerInfo.RankingPoints + 28;
			int32 playerPoints = playerInfo.RankingPoints - 28;
			playerInfo.RankingPoints = playerPoints < 0 ? 0 : playerPoints;
			// Battle Ended
			FTimerHandle timer;
			FTimerDelegate TDelegate;
			TDelegate.BindUFunction(this, FName("ClientTravel"), TEXT("MainMenuMap"), ETravelType::TRAVEL_Absolute);
			GetWorldTimerManager().SetTimer(timer, TDelegate, 3.f, false);
		}
		else
		{
			// Remove Polymons & Start Selecting
			FTimerHandle timer;
			GetWorldTimerManager().SetTimer(timer, this, &ABattlePC::RestartRound, 3.f, false);
		}
	}
}

void ABattlePC::CL_StartSelecting_Implementation()
{
	BattleHUDRef->StartSelecting(AvailablePolymons);
}