// * Copyright © 2025, Nathan Adotey. All Rights Reserved.

#pragma once

#include "Data/CStructures.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatSystem.generated.h"

// * --- Declare function delegates for certain combat events

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGroundAttack, FComboInfo, comboInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAirAttack);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGroundSlam);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGroundRushAttack);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAerialRushAttack);

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

	// * Function delegate which invokes a callback method when an aerial attack has been executed
	UPROPERTY(BlueprintAssignable)
	FOnAirAttack OnAirAttack;

	// * Function delegate which invokes a callback method when a ground slam has been executed
	UPROPERTY(BlueprintAssignable)
	FOnGroundSlam OnGroundSlam;

	// * Function delegate which invokes a callback method when a ground rush attack has been executed
	UPROPERTY(BlueprintAssignable)
	FOnGroundRushAttack OnGroundRushAttack;

	// * Function delegate which invokes a callback method when an aerial rush attack has been executed
	UPROPERTY(BlueprintAssignable)
	FOnAerialRushAttack OnAerialRushAttack;

public:
	// * Static combat data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat System")
	FCombatData combatData;

	// * Determines knockback and visual effect parameters when an attack lands
	UPROPERTY(BlueprintReadWrite, Category = "Combat Properties")
	EDamageImpact damageImpact;

	// * Repository of combo tags (Enable extended combos)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Properties")
	TArray<FName> comboTags;

private:
	// * Used to track the current attack input
	EComboInput currentComboInput;

	// * Used to cache the previous attack input
	EComboInput previousComboInput;

	// * Current combo count
	unsigned short int currentComboCount;

	TArray<FComboInfo> comboData;
	TArray<FName> comboTag;

public:
	// * Attempt to execute a ground or aerial attack combo
	UFUNCTION(BlueprintCallable, Category = "Combat System")
	void Attack(EComboInput comboInput);

	// * Attempt to override a ground or aerial attack combo
	UFUNCTION(BlueprintCallable, Category = "Combat System")
	void OverrideAttack(EComboInput comboInput, FComboInfo overrideComboData);

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

	// * Returns TRUE if the player can execute an attack while sprinting (Conditions set within the editor)
	UFUNCTION(BlueprintImplementableEvent)
	bool CanSprintAttack();

	// * Returns TRUE if the player can execute an attack after dodging (Conditions set within the editor)
	UFUNCTION(BlueprintImplementableEvent)
	bool CanDodgeAttack();

	// * Returns TRUE if the player can override their default ground combo sequence (Conditions set within the editor)
	UFUNCTION(BlueprintImplementableEvent)
	bool CanOverrideAttack();

private:
	void PlayAttackMontage(FComboInfo comboInfo);
	void UpdateComboInfoArrays(EComboInput comboInput);
};

// * Copyright © 2025, Nathan Adotey. All Rights Reserved.