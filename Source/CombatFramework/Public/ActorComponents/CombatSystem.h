// * Copyright © 2025, Nathan Adotey. All Rights Reserved.

#pragma once

#include "Data/CStructures.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatSystem.generated.h"

// * --- Declare function delegates for certain combat events

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGroundAttack, FComboInfo, comboInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDefensiveEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Abstract, Blueprintable, DefaultToInstanced )
class COMBATFRAMEWORK_API UCombatSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// * Constructor
	UCombatSystem();

	// * Function delegate which invokes a callback method when a ground attack has been executed
	UPROPERTY(BlueprintAssignable)
	FOnGroundAttack OnGroundAttack;

	// * Function delegate which invokes a callback method when a defensive event has been executed (e.g. Block, parry)
	UPROPERTY(BlueprintAssignable)
	FOnDefensiveEvent OnDefensiveEvent;

public:
	// * Static combat data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat System")
	FCombatData combatData;

	// * Current skill payload
	UPROPERTY(BlueprintReadOnly, Category = "Combat System")
	FComboInfo currentSkillPayload;

	// * Repository of combo tags (Enable extended combos)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Properties")
	TArray<FName> comboTags;

	// * Determines knockback and visual effect parameters when an attack lands
	UPROPERTY(BlueprintReadWrite, Category = "Combat Properties")
	EDamageImpact damageImpact;

private:
	// * Used to track the current attack input
	EComboInput currentComboInput;

	// * Used to cache the previous attack input
	EComboInput previousComboInput;

	// * Current combo count
	unsigned short int currentComboCount;

public:
	// * Attempt to execute a ground or aerial attack combo
	UFUNCTION(BlueprintCallable, Category = "Combat System")
	void Attack(EComboInput comboInput);

	// * Attempt to execute a ground or aerial defensive action (e.g. Block, parry)
	UFUNCTION(BlueprintCallable, Category = "Combat System")
	void DefensiveEvent();

	// * Attempt to override a ground or aerial attack combo
	UFUNCTION(BlueprintCallable, Category = "Combat System")
	void OverrideAttack(EComboInput comboInput, FComboInfo overrideComboData);

	// * Attempt to execute a ground or aerial attack combo
	UFUNCTION(BlueprintCallable, Category = "Combat System")
	void Skill(FComboInfo skillPayload);

	// * Reset the current combo count to 0
	UFUNCTION(BlueprintCallable, Category = "Combat System")
	void ResetComboCount();

	// * Returns the current combo index
	UFUNCTION(BlueprintPure, Category = "Combat System")
	const int GetCurrentComboCount();

public:
	// * Returns TRUE if the player is in the air, FALSE if not (Conditions set within the editor)
	UFUNCTION(BlueprintImplementableEvent)
	bool GetAerialStatus();

	// * Returns TRUE if the player can execute an attack combo (Conditions set within the editor)
	UFUNCTION(BlueprintImplementableEvent)
	bool CanAttack();

	// * Returns TRUE if the player can perform a defensive action such as blocking or parrying (Conditions set within the editor)
	UFUNCTION(BlueprintImplementableEvent)
	bool CanUseDefensiveEvent();

	// * Returns TRUE if the player can override their default ground combo sequence (Conditions set within the editor)
	UFUNCTION(BlueprintImplementableEvent)
	bool CanOverrideAttack();

private:
	void PlayAttackMontage(FComboInfo comboInfo);
	bool TestComboTag(FName comboTag);
};

// * Copyright © 2025, Nathan Adotey. All Rights Reserved.