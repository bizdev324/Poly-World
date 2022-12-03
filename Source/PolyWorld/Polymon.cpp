// Fill out your copyright notice in the Description page of Project Settings.


#include "Polymon.h"
#include "Kismet/KismetMathLibrary.h"
#include "BattlePC.h"

// Sets default values
APolymon::APolymon()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);
	SetReplicateMovement(true);
	// 
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetMesh());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90.f));
	SpringArm->SetRelativeLocation(FVector(0, 200.f, 160.f));
	SpringArm->TargetArmLength = 550;
	bUseControllerRotationYaw = false;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APolymon::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//
	DOREPLIFETIME(APolymon, PolymonInfo);
	DOREPLIFETIME(APolymon, CurrentHealth);
	DOREPLIFETIME(APolymon, CurrentPolydust);
	DOREPLIFETIME(APolymon, bIsDead);
	DOREPLIFETIME(APolymon, ActionIndex);
	DOREPLIFETIME(APolymon, bCanPlay);
}

// Called when the game starts or when spawned
void APolymon::BeginPlay()
{
	Super::BeginPlay();
	//
	if (!PolymonInfo.Name.IsEmpty() && !IsLocallyControlled())
	{
		SetModel();
	}
}

void APolymon::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//
	SR_SetHUDWithPolymon();
}

void APolymon::SR_SetHUDWithPolymon_Implementation()
{
	OwnerPC->CL_UpdatePlayerHealth(CurrentHealth / PolymonInfo.Health);
	OwnerPC->Opponent->CL_UpdateOpponentHealth(CurrentHealth / PolymonInfo.Health);
	OwnerPC->CL_SetHUDWithPolymon();
}

// Called every frame
void APolymon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APolymon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//

}

void APolymon::SetModel()
{
	if (PolymonInfo.Model != nullptr)
	{
		GetMesh()->SetSkeletalMesh(PolymonInfo.Model);
		GetMesh()->SetAnimClass(PolymonInfo.AnimationBP);
	}
}

void APolymon::MC_SetModel_Implementation()
{
	SetModel();
}

void APolymon::StartPolydustGenerationTimer_Implementation()
{
	bCanPlay = true;
	GetWorldTimerManager().SetTimer(TPolydustGenerationHandle, this, &APolymon::AddPolydust, 2.8,true);
}

void APolymon::StopPolydustGenerationTimer_Implementation()
{
	TPolydustGenerationHandle.Invalidate();
}

void APolymon::EndDefending()
{
	bIsDefending = false;
	DefendingRatio = 1.f;
	UE_LOG(LogTemp, Warning, TEXT("Stopped Defending"));
}

void APolymon::AddPolydust_Implementation()
{
	if (FreezedPolydust > 0)
	{
		FreezedPolydust--;
		return;
	}
	if (CurrentPolydust < 10)
	{
		CurrentPolydust++;
	}
	CL_UpdatePolydust(CurrentPolydust);
}

void APolymon::CL_UpdatePolydust_Implementation(int32 NewPolydust)
{
	OnPolyDustChange.Broadcast(NewPolydust);
}

float APolymon::GetTypeEffectivness(const FPolymonInfo& OpponentPolymon)
{
	float total = 1.f;
	// check weakness
	for (EPowerType strength : PolymonInfo.Strengths)
	{
		for (EPowerType weakness : OpponentPolymon.Weaknesses)
		{
			if (strength == weakness)
			{
				total *= 2.f;
			}
		}
	}
	if (PolymonInfo.Type == OpponentPolymon.Type)
	{
		total *= 0.5f;
	}
	return total;
}

void APolymon::PhysicalAttack(const FActionInfo& ActionInfo)
{
	// Play Action Animation
	bool success = FMath::FRand()*100.f <= ActionInfo.Accuracy;
	if (success)
	{
		FPolymonInfo Opp = OwnerPC->Opponent->SpawnedPolymon->PolymonInfo;
		//
		float CRITICALHIT = FMath::FRand() <= 0.06f? 2.f : 1.f;
		float RANDOM = FMath::FRandRange(210.f, 250.f) / 250.f;
		float POLYLEVEL = (float)PolymonInfo.Level;
		float ATTACKPOWER = (float) ActionInfo.Power;
		float POLYATTACK = (float)PolymonInfo.Attack;
		float OPPONENTDEFENCE = (float)Opp.Defense;
		float TYPE1EFFECTIVE = GetTypeEffectivness(Opp);
		float OPPONENTDEFENDING = OwnerPC->Opponent->SpawnedPolymon->DefendingRatio;
		float DamageApplied = OPPONENTDEFENDING * (((((((2.f * POLYLEVEL * CRITICALHIT) / 5.f) + 2.f) * ATTACKPOWER * (POLYATTACK / OPPONENTDEFENCE)) / 50.f) + 2.f) * TYPE1EFFECTIVE * RANDOM);
		FPointDamageEvent DamageEvent(DamageApplied, FHitResult(), FVector(), nullptr);
		OwnerPC->Opponent->SpawnedPolymon->TakeDamage(DamageApplied, DamageEvent, OwnerPC, this);
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Attack Failed"));
}

void APolymon::SpecialAttack(const FActionInfo& ActionInfo)
{
	// Play Action Animation
	bool success = FMath::FRand() * 100.f <= ActionInfo.Accuracy;
	if (success)
	{
		FPolymonInfo Opp = OwnerPC->Opponent->SpawnedPolymon->PolymonInfo;
		//
		float CRITICALHIT = FMath::FRand() <= 0.06f ? 2.f : 1.f;
		float RANDOM = FMath::FRandRange(210.f, 250.f) / 250.f;
		float POLYLEVEL = (float)PolymonInfo.Level;
		float ATTACKPOWER = (float)ActionInfo.Power;
		float POLYATTACK = (float)PolymonInfo.SpecialAttack;
		float OPPONENTDEFENCE = (float)Opp.SpecialDefense;
		float TYPE1EFFECTIVE = GetTypeEffectivness(Opp);
		float OPPONENTDEFENDING = OwnerPC->Opponent->SpawnedPolymon->DefendingRatio;
		float DamageApplied = OPPONENTDEFENDING * (((((((2.f * POLYLEVEL * CRITICALHIT) / 5.f) + 2.f) * ATTACKPOWER * (POLYATTACK / OPPONENTDEFENCE)) / 50.f) + 2.f) * TYPE1EFFECTIVE * RANDOM);
		FPointDamageEvent DamageEvent(DamageApplied, FHitResult(),FVector(),nullptr);
		OwnerPC->Opponent->SpawnedPolymon->TakeDamage(DamageApplied, DamageEvent, OwnerPC, this);
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Attack Failed"));
}
void APolymon::Defense(const FActionInfo& ActionInfo)
{
	// Play Action Animation
	bool success = FMath::FRand() * 100.f <= ActionInfo.Accuracy;
	if (success)
	{
		DefendingRatio = 1.f - FMath::FRandRange((float)ActionInfo.MinEfficiency, (float)ActionInfo.MaxEfficiency) / 100.f;
		bIsDefending = true;
		GetWorldTimerManager().SetTimer(TDefendingHandle, this, &APolymon::EndDefending, ActionInfo.Duration, false);
		UE_LOG(LogTemp, Warning, TEXT("Defending"));
	}
}
void APolymon::SpecialDefense(const FActionInfo& ActionInfo)
{
	// Play Action Animation
	bool success = FMath::FRand() * 100.f <= ActionInfo.Accuracy;
	if (success)
	{
		DefendingRatio = 1.f - FMath::FRandRange((float)ActionInfo.MinEfficiency, (float)ActionInfo.MaxEfficiency) / 100.f;
		bIsDefending = true;
		GetWorldTimerManager().SetTimer(TDefendingHandle, this, &APolymon::EndDefending, ActionInfo.Duration, false);
		UE_LOG(LogTemp, Warning, TEXT("Defending"));
	}
}
void APolymon::Stun(const FActionInfo& ActionInfo)
{
	// Play Action Animation
	bool success = FMath::FRand() * 100.f <= ActionInfo.Accuracy;
	if (success)
	{
		OwnerPC->Opponent->SpawnedPolymon->FreezedPolydust = ActionInfo.Power;
		UE_LOG(LogTemp, Warning, TEXT("Stun Sucess"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Stun Failed"));
}

float APolymon::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	CurrentHealth = FMath::Clamp(CurrentHealth-DamageAmount, 0.f,(float) PolymonInfo.Health);
	OwnerPC->CL_UpdatePlayerHealth(CurrentHealth/ PolymonInfo.Health);
	OwnerPC->Opponent->CL_UpdateOpponentHealth(CurrentHealth / PolymonInfo.Health);
	UE_LOG(LogTemp, Warning, TEXT("Damage Applied: %f"), DamageAmount);
	if (CurrentHealth <= 0.f)
	{
		// Death
		bIsDead = true;
		bCanPlay = false;
		OwnerPC->Opponent->bCanPlay = false;
		OwnerPC->OnPolymonDeath();
	}
	return 1;
}

void APolymon::MC_PlayMontage_Implementation(UAnimMontage* ActionMontage)
{
	PlayAnimMontage(ActionMontage);
}

void APolymon::SR_StartAction_Implementation(int32 Index)
{
	if (bCanPlay && CurrentPolydust >= PolymonInfo.ActionList[ActionIndex].PolydustCost)
	{
		CurrentPolydust -= PolymonInfo.ActionList[ActionIndex].PolydustCost;
		CL_UpdatePolydust(CurrentPolydust);
		//
		ActionIndex = Index;
		if (PolymonInfo.ActionList[ActionIndex].ActionMontage != nullptr)
		{
			MC_PlayMontage(PolymonInfo.ActionList[ActionIndex].ActionMontage);
			bCanPlay = false;
			return;
		}
		else
		{
			SR_DoAction();
		}
	}
}

void APolymon::SR_DoAction_Implementation()
{
	switch (PolymonInfo.ActionList[ActionIndex].Type)
	{
	case EActionType::PhysicalAttack:
		PhysicalAttack(PolymonInfo.ActionList[ActionIndex]);
		break;
	case EActionType::SpecialAttack:
		SpecialAttack(PolymonInfo.ActionList[ActionIndex]);
		break;
	case EActionType::Defense:
		Defense(PolymonInfo.ActionList[ActionIndex]);
		break;
	case EActionType::SpecialDefense:
		SpecialDefense(PolymonInfo.ActionList[ActionIndex]);
		break;
	case EActionType::Stun:
		Stun(PolymonInfo.ActionList[ActionIndex]);
		break;
	default:
		;
		break;
	}
}

void APolymon::SR_EndAction_Implementation()
{
	bCanPlay = true;
}