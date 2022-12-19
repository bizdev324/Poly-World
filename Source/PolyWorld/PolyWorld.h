// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PolyWorld.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8 
{
	PhysicalAttack = 0 UMETA(DisplayName = "Physical Attack"),
	SpecialAttack = 1 UMETA(DisplayName = "Special Attack"),
	SpecialDefense = 2     UMETA(DisplayName = "SpecialDefense"),
	Defense = 3     UMETA(DisplayName = "Defense"),
	Stun = 4  UMETA(DisplayName = "Stun")
};

UENUM(BlueprintType)
enum class EGenderType : uint8
{
	Male = 0 UMETA(DisplayName = "Male"),
	Female = 1 UMETA(DisplayName = "Female")
};

UENUM(BlueprintType)
enum class EPowerType : uint8
{
	Normal = 0 UMETA(DisplayName = "Normal"),
	Fire = 1 UMETA(DisplayName = "Fire"),
	Water = 1 UMETA(DisplayName = "Water"),
	Ice = 3 UMETA(DisplayName = "Ice"),
	Rock = 4 UMETA(DisplayName = "Rock"),
	Electric = 5 UMETA(DisplayName = "Electric"),
	Flying = 6 UMETA(DisplayName = "Flying"),
	Fairy = 7 UMETA(DisplayName = "Fairy"),
	Fighting = 8 UMETA(DisplayName = "Fighting"),
	Posion = 9 UMETA(DisplayName = "Posion"),
	Ground = 10 UMETA(DisplayName = "Ground"),
	Ghost = 11 UMETA(DisplayName = "Ghost"),
	Dark = 12 UMETA(DisplayName = "Dark"),
	Steel = 13 UMETA(DisplayName = "Steel"),
	Grass = 14 UMETA(DisplayName = "Grass"),
	Bug = 15 UMETA(DisplayName = "Bug"),
	Psychic = 16 UMETA(DisplayName = "Psychic")
};

USTRUCT(BlueprintType)
struct FActionInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		FString Name = TEXT("");
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		EActionType Type = EActionType::PhysicalAttack;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		UTexture2D* Image;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		int32 PolydustCost = 0;
		// Accuracy =OR= Chances for Defense
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		int32 Accuracy = 0;
		// Power =OR= DustFreeze
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		int32 Power = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		int32 MinEfficiency = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		int32 MaxEfficiency = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		float Duration = 0.f;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		class UAnimMontage* ActionMontage;
};

USTRUCT(BlueprintType)
struct FPlayerInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	FString Name = TEXT("");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	UTexture2D* Image;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int32 EXP = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int32 Level = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int32 RankingPoints = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int32 Wins = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int32 Losses = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float Ratio = 0.f;
};

USTRUCT(BlueprintType)
struct FPolymonInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		FString Name = TEXT("");
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		FString Description = TEXT("");
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		float Height = 0.f;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		float Weight = 0.f;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		EPowerType Type = EPowerType::Normal;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		EGenderType Gender = EGenderType::Male;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		UTexture2D* Image;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		USkeletalMesh* Model;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		TSubclassOf<UAnimInstance> AnimationBP;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 Level = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 BattleEXP = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 Health = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 HealthGenes = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 Attack = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 AttackGenes = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 Defense = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 DefenseGenes = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 SpecialAttack = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 SpecialAttackGenes = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 SpecialDefense = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 SpecialDefenseGenes = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 Speed = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 SpeedGenes = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		class UAnimMontage* HitMontage;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		FString EvolutionName = TEXT("");
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		TArray<EPowerType> Strengths;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		TArray<EPowerType> Weaknesses;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		TArray<FActionInfo> ActionList;
};

