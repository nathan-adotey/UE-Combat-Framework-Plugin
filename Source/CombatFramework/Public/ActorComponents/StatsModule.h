// * Copyright © 2025, Nathan Adotey. All Rights Reserved.

#pragma once

#include "Data/CStructures.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsModule.generated.h"

// * --- Declare delegates

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterStatsUpdated, FStatSchema, stats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthModified, float, health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaModified, float, mana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterDeath);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMBATFRAMEWORK_API UStatsModule : public UActorComponent
{
	GENERATED_BODY()

public:	
	// * Constructor
	UStatsModule();

	// * Callback method invoked when the player adjusts their stats
	UPROPERTY(BlueprintAssignable)
	FOnCharacterStatsUpdated OnCharacterStatsUpdated;

	// * Callback method invoked when the player restores/drains their health
	UPROPERTY(BlueprintAssignable)
	FOnHealthModified OnHealthModified;

	// * Callback method invoked when the player restores/drains their mana
	UPROPERTY(BlueprintAssignable)
	FOnManaModified OnManaModified;

	// * Callback method invoked when the player dies
	UPROPERTY(BlueprintAssignable)
	FOnCharacterDeath OnCharacterDeath;

public:
	// * Actor name
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Basic Info")
	FText name;

	// * Maximum health value
	UPROPERTY(BlueprintReadOnly, Category = "Base Stats",
		meta = (
			UIMin = "0",
			ClampMin = "0"
		)
	)
	float maximumHealth;

	// * Maximum mana value
	UPROPERTY(BlueprintReadOnly, Category = "Base Stats",
		meta = (
			UIMin = "0",
			ClampMin = "0"
		)
	)
	float maximumMana;

	// * Current health value
	UPROPERTY(BlueprintReadOnly, Category = "Base Stats",
		meta = (
			UIMin = "0",
			ClampMin = "0"
		)
	)
	float currentHealth;

	// * Current mana value
	UPROPERTY(BlueprintReadOnly, Category = "Base Stats",
		meta = (
			UIMin = "0",
			ClampMin = "0"
		)
	)
	float currentMana;

	// * Player stats & resistances
	UPROPERTY(BlueprintReadOnly, Category = "Base Stats")
	FStatSchema playerStats;
	
	// * Player stats & resistances - Exposed to the editor and may override the player's current stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	FStatSchema testStats;

	UPROPERTY(EditDefaultsOnly, Category = "Debug")
	bool bUseTestStats;

public:
	// * Initialize maximum health & mana based on the player's current stats
	UFUNCTION(BlueprintCallable)
	void InitializeStats(const bool bHeal);

	// * Fully restore health and mana
	UFUNCTION(BlueprintCallable)
	void RecoverAllStats();

	// * Returns the current health as a value between 0 & 1
	UFUNCTION(BlueprintPure)
	const float GetCurrentHealthPercentage();

	// * Returns the current mana as a value between 0 & 1
	UFUNCTION(BlueprintPure)
	const float GetCurrentManaPercentage();

	// * Restore health by a set amount
	UFUNCTION(BlueprintCallable)
	void RestoreHealth(const float amount);

	// * Drain health by a set amount
	UFUNCTION(BlueprintCallable)
	void DrainHealth(const float amount);

	// * Restore mana by a set amount
	UFUNCTION(BlueprintCallable)
	void RestoreMana(const float amount);

	// * Drain mana by a set amount
	UFUNCTION(BlueprintCallable)
	void DrainMana(const float amount);

	// * Calculate physical weapon damage
	UFUNCTION(BlueprintPure)
	const float CalculatePhysicalWeaponDamage(FCombatData combatProfile);

	// * Calculate ki weapon damage
	UFUNCTION(BlueprintPure)
	const float CalculateKiWeaponDamage(FCombatData combatProfile);

	// * Calculate arcane weapon damage
	UFUNCTION(BlueprintPure)
	const float CalculateArcaneWeaponDamage(FCombatData combatProfile);

private:
	const float CalculateMaximumHealth();
	const float CalculateMaximumMana();
};

// * Copyright © 2025, Nathan Adotey. All Rights Reserved.