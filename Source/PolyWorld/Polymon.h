// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PolyWorld.h"
#include "TimerManager.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "Polymon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPolyDustChangeDelegate, int32, Polydust);

UCLASS()
class POLYWORLD_API APolymon : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APolymon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	virtual void PossessedBy(AController* NewController) override;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* Camera;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArm;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
	class ABattlePC* OwnerPC;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Polymon")
	FPolymonInfo PolymonInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Polymon")
	float CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Polymon")
	int32 CurrentPolydust = 6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
	int32 FreezedPolydust = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
	bool bIsDefending = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Polymon")
	FActionInfo DefendingAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Polymon")
	bool bIsDead = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Polymon")
	bool bCanPlay = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Polymon")
	int32 ActionIndex;

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "Polymon")
	void MC_SetModel();
	UFUNCTION(BlueprintCallable, Category = "Polymon")
	void SetModel();
	UFUNCTION(BlueprintCallable, Category = "Polymon")
	float GetHealthRatio() const { return CurrentHealth / (float)PolymonInfo.Health; };
	UFUNCTION(BlueprintCallable, Category = "Polymon")
	float GetDefendingRatio();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	FTimerHandle TPolydustGenerationHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	FTimerHandle TDefendingHandle;
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Polymon")
	void StartPolydustGenerationTimer(float Seconds);
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Polymon")
	void StopPolydustGenerationTimer();
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Polymon")
	void AddPolydust();

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Polymon")
	void CL_UpdatePolydust(int32 NewPolydust);
	// Playing Montage
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "Polymon")
	void MC_PlayMontage(UAnimMontage* ActionMontage, FName StartSectionName);
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "Polymon")
	void OC_PlayMontage(UAnimMontage* ActionMontage, FName StartSectionName);
	UFUNCTION(BlueprintCallable, Category = "Polymon")
	void PlayMontage(UAnimMontage* ActionMontage, FName StartSectionName);
	//
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Polymon")
	void SR_StartAction(int32 ListIndex, const FActionInfo& ActionInfo);
	//
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Polymon")
	void SR_DoAction();
	//
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Polymon")
	void SR_EndAction();
	//
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Polymon")
	void SR_EndDefending();
	//
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Polymon")
	void SR_EndHit();
	//
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Polymon")
	void SR_SetHUDWithPolymon();
	//
	UFUNCTION(BlueprintCallable, Category = "Polymon")
	float GetTypeEffectivness(const FPolymonInfo& OpponentPolymon);

	UFUNCTION(BlueprintCallable, Category = "Polymon")
	void PhysicalAttack(const FActionInfo& ActionInfo);
	UFUNCTION(BlueprintCallable, Category = "Polymon")
	void SpecialAttack(const FActionInfo& ActionInfo);
	UFUNCTION(BlueprintCallable, Category = "Polymon")
	void Defense(const FActionInfo& ActionInfo);
	UFUNCTION(BlueprintCallable, Category = "Polymon")
	void SpecialDefense(const FActionInfo& ActionInfo);
	UFUNCTION(BlueprintCallable, Category = "Polymon")
	void Stun(const FActionInfo& ActionInfo);

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	UFUNCTION()
	int32 GetActionIndex(const FActionInfo& action);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintAssignable, Category = "Polymon")
	FOnPolyDustChangeDelegate OnPolyDustChange;


};
