// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PolyWorld.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8 
{
	PhysicalAttack = 0 UMETA(DisplayName = "Attack"),
	SpecialAttack = 1 UMETA(DisplayName = "Special Attack"),
	SpecialDefense = 2     UMETA(DisplayName = "SpecialDefense"),
	Defense = 3     UMETA(DisplayName = "Defensive"),
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
	AllTypes = 0 UMETA(DisplayName = "All Types"),
	Normal = 1 UMETA(DisplayName = "Normal"),
	Fire = 2 UMETA(DisplayName = "Fire"),
	Water = 3 UMETA(DisplayName = "Water"),
	Grass = 4 UMETA(DisplayName = "Grass"),
	Electric = 5 UMETA(DisplayName = "Electric"),
	Ice = 6 UMETA(DisplayName = "Ice"),
	Fighting = 7 UMETA(DisplayName = "Fighting"),
	Poison = 8 UMETA(DisplayName = "Poison"),
	Ground = 9 UMETA(DisplayName = "Ground"),
	Flying = 10 UMETA(DisplayName = "Flying"),
	Phychic = 11 UMETA(DisplayName = "Phychic"),
	Bug = 12 UMETA(DisplayName = "Bug"),
	Rock = 13 UMETA(DisplayName = "Rock"),
	Ghost = 14 UMETA(DisplayName = "Ghost"),
	Dark = 15 UMETA(DisplayName = "Dark"),
	Dragon = 16 UMETA(DisplayName = "Dragon"),
	Steel = 17 UMETA(DisplayName = "Steel"),
	Fairy = 18 UMETA(DisplayName = "Fairy")
};

USTRUCT(BlueprintType)
struct FActionInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		FString Name = TEXT("");
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		EPowerType PowerType = EPowerType::AllTypes;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		EActionType ActionType = EActionType::PhysicalAttack;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		UTexture2D* Image;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		int32 PolydustCost = 0;
		// Power =OR= DustFreeze
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		int32 Power = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		int32 Accuracy = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		int32 MinEfficiency = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		int32 MaxEfficiency = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		float Duration = 0.f;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generated")
		FString CharacterId = TEXT("");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static ")
		FString Name = TEXT("");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static")
		FString Description = TEXT("");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static")
		float Height = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static")
		float Weight = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static")
		EPowerType Type = EPowerType::Normal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unique")
		EGenderType Gender = EGenderType::Male;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static")
		UTexture2D* Image;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static")
		USkeletalMesh* Model;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static")
		TSubclassOf<UAnimInstance> AnimationBP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unique")
		int32 Level = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unique")
		int32 BattleEXP = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unique")
		int32 Health = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static")
		int32 HealthGenes = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unique")
		int32 Attack = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static")
		int32 AttackGenes = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unique")
		int32 Defense = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static")
		int32 DefenseGenes = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unique")
		int32 SpecialAttack = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static")
		int32 SpecialAttackGenes = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unique")
		int32 SpecialDefense = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static")
		int32 SpecialDefenseGenes = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unique")
		int32 Speed = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static")
		int32 SpeedGenes = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static")
		class UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static")
		class UAnimMontage* DefenseMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static")
		class UAnimMontage* HitMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static")
		FString EvolutionName = TEXT("");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static")
		TArray<EPowerType> Strengths;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static")
		TArray<EPowerType> Weaknesses;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unique")
		TArray<int32> ActionKeys;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generated")
		TArray<FActionInfo> ActionList;
};