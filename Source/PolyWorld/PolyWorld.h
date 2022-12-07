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
		FString Name;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		EActionType Type;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		UTexture2D* Image;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		int32 PolydustCost;
		// Accuracy =OR= Chances for Defense
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		int32 Accuracy;
		// Power =OR= DustFreeze
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		int32 Power;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		int32 MinEfficiency;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		int32 MaxEfficiency;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		float Duration;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
		class UAnimMontage* ActionMontage;
};

USTRUCT(BlueprintType)
struct FPlayerInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	UTexture2D* Image;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int32 EXP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int32 Wins;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int32 Losses;
};

USTRUCT(BlueprintType)
struct FPolymonInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		FString Name;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		FString Description;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		float Height;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		float Weight;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		EPowerType Type;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		EGenderType Gender;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		UTexture2D* Image;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		USkeletalMesh* Model;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		TSubclassOf<UAnimInstance> AnimationBP;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 Level;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 BattleEXP;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 Health;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 HealthGenes;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 Attack;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 AttackGenes;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 Defense;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 DefenseGenes;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 SpecialAttack;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 SpecialAttackGenes;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 SpecialDefense;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 SpecialDefenseGenes;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 Speed;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		int32 SpeedGenes;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		class UAnimMontage* HitMontage;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		FString EvolutionName;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		TArray<EPowerType> Strengths;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		TArray<EPowerType> Weaknesses;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
		TArray<FActionInfo> ActionList;
};

