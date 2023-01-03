// Fill out your copyright notice in the Description page of Project Settings.


#include "PolyWorldGameInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayfabGSDK.h"
#include "GSDKUtils.h"

DEFINE_LOG_CATEGORY(LogPlayFabGSDKGameInstance);

void UPolyWorldGameInstance::Init()
{
	Super::Init();
	//
	if (IsDedicatedServerInstance() == true)
	{
		FOnGSDKShutdown_Dyn OnGsdkShutdown;
		OnGsdkShutdown .BindDynamic(this, &UPolyWorldGameInstance::OnGSDKShutdown);
		FOnGSDKHealthCheck_Dyn OnGsdkHealthCheck;
		OnGsdkHealthCheck.BindDynamic(this, &UPolyWorldGameInstance::OnGSDKHealthCheck);
		FOnGSDKServerActive_Dyn OnGSDKServerActive;
		OnGSDKServerActive.BindDynamic(this, &UPolyWorldGameInstance::OnGSDKServerActive);
		FOnGSDKReadyForPlayers_Dyn OnGSDKReadyForPlayers;
		OnGSDKReadyForPlayers.BindDynamic(this, &UPolyWorldGameInstance::OnGSDKReadyForPlayers);

		UGSDKUtils::RegisterGSDKShutdownDelegate(OnGsdkShutdown);
		UGSDKUtils::RegisterGSDKHealthCheckDelegate(OnGsdkHealthCheck);
		UGSDKUtils::RegisterGSDKServerActiveDelegate(OnGSDKServerActive);
		UGSDKUtils::RegisterGSDKReadyForPlayers(OnGSDKReadyForPlayers);
	}
#if UE_SERVER
	UGSDKUtils::SetDefaultServerHostPort();
#endif
}

void UPolyWorldGameInstance::OnStart()
{
	Super::OnStart();
	//
	UE_LOG(LogPlayFabGSDKGameInstance, Warning, TEXT("Reached onStart!"));
	UGSDKUtils::ReadyForPlayers();
}

FPolymonInfo UPolyWorldGameInstance::GetSelectedPolymon(int32 Index)
{
	if (SelectedPolymons.Num() > Index)
	{
		return SelectedPolymons[Index];
	}
	FPolymonInfo empty;
	return empty;
}

TArray<FPolymonInfo> UPolyWorldGameInstance::GetAvailablePolymons()
{
	return AvailablePolymons;
}

void UPolyWorldGameInstance::SetSelectedPolymons(const TArray<FPolymonInfo>& SelectedPolys)
{
	SelectedPolymons = SelectedPolys;
}

FPlayerInfo UPolyWorldGameInstance::GetPlayerInfo()
{
	return PlayerInfo;
}

void UPolyWorldGameInstance::SR_GenerateNewPolymonInfo_Implementation(const FPolymonInfo& polymonTemplate, const FPlayerInfo& Player)
{
	// Prepare Data
	FPolymonInfo NewPolymon = polymonTemplate;
	float POLYMONBATTLEEXPERIENCE = polymonTemplate.BattleEXP;
	float PLAYEREXPERIENCE = Player.EXP;
	int32 LEVEL = Player.Level;
	// Generate Health
	float HEALTH = polymonTemplate.Health;
	float HEALTHGENES = polymonTemplate.HealthGenes;
	NewPolymon.Health = FMath::RoundToInt((((HEALTH + HEALTHGENES) * 2.f + ((POLYMONBATTLEEXPERIENCE + PLAYEREXPERIENCE) / 4.f)) * LEVEL) / 100.f) + LEVEL + 10;
	// Generate Attack
	float ATTACK = polymonTemplate.Attack;
	float ATTACKGENES = polymonTemplate.AttackGenes;
	NewPolymon.Attack = FMath::RoundToInt((((ATTACK + ATTACKGENES) * 2.f + ((POLYMONBATTLEEXPERIENCE + PLAYEREXPERIENCE) / 4.f)) * LEVEL) / 100.f) + LEVEL;
	// Generate Special Attack
	float SPECIALATTACK = polymonTemplate.SpecialAttack;
	float SPECIALATTACKGENES = polymonTemplate.SpecialAttackGenes;
	NewPolymon.SpecialAttack = FMath::RoundToInt((((SPECIALATTACK + SPECIALATTACKGENES) * 2.f + ((POLYMONBATTLEEXPERIENCE + PLAYEREXPERIENCE) / 4.f)) * LEVEL) / 100.f) + LEVEL;
	// Generate Defense
	float DEFENSE = polymonTemplate.Defense;
	float DEFENSEGENES = polymonTemplate.DefenseGenes;
	NewPolymon.Defense = FMath::RoundToInt((((DEFENSE + DEFENSEGENES) * 2.f + ((POLYMONBATTLEEXPERIENCE + PLAYEREXPERIENCE) / 4.f)) * LEVEL) / 100.f) + LEVEL;
	// Generate Special Defense
	float SPECIALDEFENSE = polymonTemplate.SpecialDefense;
	float SPECIALDEFENSEGENES = polymonTemplate.SpecialDefenseGenes;
	NewPolymon.SpecialDefense = FMath::RoundToInt((((SPECIALDEFENSE + SPECIALDEFENSEGENES) * 2.f + ((POLYMONBATTLEEXPERIENCE + PLAYEREXPERIENCE) / 4.f)) * LEVEL) / 100.f) + LEVEL;
	// Generate Speed
	float SPEED = polymonTemplate.Speed;
	float SPEEDGENES = polymonTemplate.SpeedGenes;
	NewPolymon.Speed = FMath::RoundToInt((((SPEED + SPEEDGENES) * 2.f + ((POLYMONBATTLEEXPERIENCE + PLAYEREXPERIENCE) / 4.f)) * LEVEL) / 100.f) + LEVEL;
	// return ??

}

void UPolyWorldGameInstance::OnGSDKShutdown()
{
	UE_LOG(LogPlayFabGSDKGameInstance, Warning, TEXT("Shutdown!"));
	FPlatformMisc::RequestExit(false);
}

bool UPolyWorldGameInstance::OnGSDKHealthCheck()
{
	UE_LOG(LogPlayFabGSDKGameInstance, Warning, TEXT("Healthy!"));
	return true;
}

void UPolyWorldGameInstance::OnGSDKServerActive()
{
	/**
	 * Server is transitioning to an active state.
	 * Optional: Add in the implementation any code that is needed for the game server when
	 * this transition occurs.
	 */
	UE_LOG(LogPlayFabGSDKGameInstance, Warning, TEXT("Active!"));
}

void UPolyWorldGameInstance::OnGSDKReadyForPlayers()
{
	/**
	 * Server is transitioning to a StandBy state. Game initialization is complete and the game is ready
	 * to accept players.
	 * Optional: Add in the implementation any code that is needed for the game server before
	 * initialization completes.
	 */
	UE_LOG(LogPlayFabGSDKGameInstance, Warning, TEXT("Finished Initialization - Moving to StandBy!"));
}

void UPolyWorldGameInstance::SavePlayerData_Implementation()
{

}
void UPolyWorldGameInstance::LoadPlayerData_Implementation()
{

}