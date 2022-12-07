// Fill out your copyright notice in the Description page of Project Settings.


#include "PolyWorldGameInstance.h"
#include "Kismet/KismetMathLibrary.h"

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