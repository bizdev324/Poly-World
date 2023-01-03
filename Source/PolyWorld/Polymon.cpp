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
	bUseControllerRotationYaw = false;
	//
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// 
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetMesh());
	SpringArm->SetRelativeLocation(FVector(10.f, 170.f, 95.f));
	SpringArm->SetRelativeRotation(FRotator(-5.f, 50.f, 0.f));
	SpringArm->TargetArmLength = 550;
	//
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->SetFieldOfView(70.f);
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

void APolymon::StartPolydustGenerationTimer_Implementation(float Seconds)
{
	bCanPlay = true;
	GetWorldTimerManager().SetTimer(TPolydustGenerationHandle, this, &APolymon::AddPolydust, Seconds,true);
}

void APolymon::StopPolydustGenerationTimer_Implementation()
{
	TPolydustGenerationHandle.Invalidate();
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
		float OPPONENTDEFENDING = OwnerPC->Opponent->SpawnedPolymon->GetDefendingRatio();
		float DamageApplied = OPPONENTDEFENDING * (((((((2.f * POLYLEVEL * CRITICALHIT) / 5.f) + 2.f) * ATTACKPOWER * (POLYATTACK / OPPONENTDEFENCE)) / 50.f) + 2.f) * TYPE1EFFECTIVE * RANDOM);
		FPointDamageEvent DamageEvent(DamageApplied, FHitResult(), FVector(), nullptr);
		OwnerPC->Opponent->SpawnedPolymon->TakeDamage(DamageApplied, DamageEvent, OwnerPC, this);
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Attack Failed"));
}

void APolymon::SpecialAttack(const FActionInfo& ActionInfo)
{
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
		float OPPONENTDEFENDING = OwnerPC->Opponent->SpawnedPolymon->GetDefendingRatio();
		float DamageApplied = OPPONENTDEFENDING * (((((((2.f * POLYLEVEL * CRITICALHIT) / 5.f) + 2.f) * ATTACKPOWER * (POLYATTACK / OPPONENTDEFENCE)) / 50.f) + 2.f) * TYPE1EFFECTIVE * RANDOM);
		FPointDamageEvent DamageEvent(DamageApplied, FHitResult(),FVector(),nullptr);
		OwnerPC->Opponent->SpawnedPolymon->TakeDamage(DamageApplied, DamageEvent, OwnerPC, this);
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Attack Failed"));
}

float APolymon::GetDefendingRatio()
{
	if (bIsDefending)
	{
		bool success = FMath::FRand() * 100.f <= DefendingAction.Accuracy;
		if (success)
		{
			UE_LOG(LogTemp, Warning, TEXT("Reduced Damage"));
			return 1.f - FMath::FRandRange((float)DefendingAction.MinEfficiency, (float)DefendingAction.MaxEfficiency) / 100.f;
		}
		UE_LOG(LogTemp, Warning, TEXT("Fail Defending"));
		SR_EndDefending();
	}
	return 1.f;
}
void APolymon::Defense(const FActionInfo& ActionInfo)
{
	bIsDefending = true;
	DefendingAction = ActionInfo;
	UE_LOG(LogTemp, Warning, TEXT("Defending"));

}
void APolymon::SpecialDefense(const FActionInfo& ActionInfo)
{
	bIsDefending = true;
	DefendingAction = ActionInfo;
	UE_LOG(LogTemp, Warning, TEXT("Defending"));

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
	UE_LOG(LogTemp, Warning, TEXT("Damage Applied: %f"), DamageAmount);
	CurrentHealth = FMath::Clamp(CurrentHealth-DamageAmount, 0.f,(float) PolymonInfo.Health);
	OwnerPC->CL_UpdatePlayerHealth(CurrentHealth/ PolymonInfo.Health);
	OwnerPC->Opponent->CL_UpdateOpponentHealth(CurrentHealth / PolymonInfo.Health);
	// Check Death
	if (CurrentHealth <= 0.f)
	{
		// Death
		bIsDead = true;
		bCanPlay = false;
		OwnerPC->Opponent->bCanPlay = false;
		OwnerPC->OnPolymonDeath();
		return 1;
	}
	if (PolymonInfo.HitMontage != nullptr)
	{
		MC_PlayMontage(PolymonInfo.HitMontage, TEXT("Default"));
		bCanPlay = false;
	}
	if (bIsDefending)
	{
		MC_PlayMontage(PolymonInfo.DefenseMontage, TEXT("EndDefend"));
	}
	return 1;
}

void APolymon::MC_PlayMontage_Implementation(UAnimMontage* ActionMontage, FName StartSectionName)
{
	PlayMontage(ActionMontage, StartSectionName);
}

void APolymon::OC_PlayMontage_Implementation(UAnimMontage* ActionMontage, FName StartSectionName)
{
	PlayMontage(ActionMontage, StartSectionName);
}

void APolymon::PlayMontage(UAnimMontage* ActionMontage, FName StartSectionName)
{
	PlayAnimMontage(ActionMontage, 1.f, StartSectionName);
	
}

void APolymon::SR_DoAction_Implementation()
{
	switch (PolymonInfo.ActionList[ActionIndex].ActionType)
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

void APolymon::SR_StartAction_Implementation(int32 Index)
{
	if (bCanPlay && CurrentPolydust >= PolymonInfo.ActionList[ActionIndex].PolydustCost)
	{
		CurrentPolydust -= PolymonInfo.ActionList[ActionIndex].PolydustCost;
		CL_UpdatePolydust(CurrentPolydust);
		//
		ActionIndex = Index;
		bCanPlay = false;
		EActionType actionType = PolymonInfo.ActionList[ActionIndex].ActionType;
		bool bIsDefense = actionType == EActionType::Defense || actionType == EActionType::SpecialDefense;
		UAnimMontage* montage = bIsDefense? PolymonInfo.DefenseMontage : PolymonInfo.AttackMontage;
		if (montage != nullptr)
		{
			if (actionType == EActionType::Defense || actionType == EActionType::SpecialDefense)
			{
				OC_PlayMontage(montage, TEXT("Default"));
			}
			else
			{
				MC_PlayMontage(montage, TEXT("Default"));
			}
			return;
		}
		else
		{
			SR_DoAction();
		}
	}
}

void APolymon::SR_EndAction_Implementation()
{
	bCanPlay = true;
	UE_LOG(LogTemp, Warning, TEXT("Attack Ended"));
}

void APolymon::SR_EndDefending_Implementation()
{
	bIsDefending = false;
	bCanPlay = true;
	UE_LOG(LogTemp, Warning, TEXT("Defend Ended"));
}

void APolymon::SR_EndHit_Implementation()
{
	if (!bIsDefending)
	{
		bCanPlay = true;
	}
	UE_LOG(LogTemp, Warning, TEXT("Hit Ended"));
}