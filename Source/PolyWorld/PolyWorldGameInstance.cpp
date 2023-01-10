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