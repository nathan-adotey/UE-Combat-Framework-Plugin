// Copyright © 2025, Nathan Adotey. All Rights Reserved.

#pragma once

#include "Data/CEnumerators.h"
#include "CStructures.generated.h"

class UWeaponProfile;

USTRUCT(BlueprintType)
struct FDamageResistances
{
	GENERATED_BODY()

public:
	// Damage resistance multiplier for physical-based attacks
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.01", UIMax = "1", ClampMin = "0.01", ClampMax = "1"))
	float defense = 0.01f;

	// Damage resistance multiplier for ki-based attacks
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.01", UIMax = "1", ClampMin = "0.01", ClampMax = "1"))
	float spirit = 0.01f;

	// Damage resistance multiplier for arcane-based attacks
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.01", UIMax = "1", ClampMin = "0.01", ClampMax = "1"))
	float faith = 0.01f;
};

USTRUCT(BlueprintType)
struct FStatSchema
{
	GENERATED_BODY()

public:
	// Current weapon level
	UPROPERTY(BlueprintReadOnly,
		meta = (
			ClampMin = "0",
			ClampMax = "200"
		)
	)
	int currentLevel;

	// Health modifier stat
	UPROPERTY(EditAnywhere, BlueprintReadOnly,
		meta = (
			ClampMin = "0",
			ClampMax = "100",
			UIMin = "0",
			UIMax = "100"
		)
	)
	int health;

	// Mana modifier
	UPROPERTY(EditAnywhere, BlueprintReadOnly,
		meta = (
			ClampMin = "0",
			ClampMax = "100",
			UIMin = "0",
			UIMax = "100"
		)
	)
	int mana;

	// Damage modifier
	UPROPERTY(EditAnywhere, BlueprintReadOnly,
		meta = (
			ClampMin = "0",
			ClampMax = "100",
			UIMin = "0",
			UIMax = "100"
		)
	)
	int strength;

	// Damage modifier
	UPROPERTY(EditAnywhere, BlueprintReadOnly,
		meta = (
			ClampMin = "0",
			ClampMax = "100",
			UIMin = "0",
			UIMax = "100"
		)
	)
	int ki;

	// Damage modifier
	UPROPERTY(EditAnywhere, BlueprintReadOnly,
		meta = (
			ClampMin = "0",
			ClampMax = "100",
			UIMin = "0",
			UIMax = "100"
		)
	)
	int arcane;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDamageResistances damageResistances;
};

USTRUCT(BlueprintType)
struct FCombatData
{
	GENERATED_BODY()

public:
	// Weapon data asset
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWeaponProfile* weaponData;

	// Current weapon level
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta = (
			ClampMin = "1",
			ClampMax = "10",
			UIMin = "1",
			UIMax = "10"
			)
	)
	int currentLevel = 1;

	// Maximum combo limit for ground attacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta = (
			ClampMin = "0",
			ClampMax = "10",
			UIMin = "0",
			UIMax = "10"
			)
	)
	int attackBonus = 0;

	// Maximum combo limit for ground attacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta = (
			ClampMin = "1",
			ClampMax = "10",
			UIMin = "1",
			UIMax = "10"
			)
	)
	int groundComboLimit = 3;

	// Maximum combo limit for air attacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta = (
			ClampMin = "1",
			ClampMax = "10",
			UIMin = "1",
			UIMax = "10"
			)
	)
	int airComboLimit = 2;

	// Auto-generates when a weapon is added to an inventory
	UPROPERTY(BlueprintReadOnly)
	int inventoryIndex;
};

USTRUCT(BlueprintType)
struct FComboInfo
{
	GENERATED_BODY()

public:
	// Attack montage
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> montage;

	// Impact hit yield different results on impact (i.e. knockbacks, normal stuns, knockdowns)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EDamageImpact damageImpact = EDamageImpact::Normal;
	
	// Modifies attack output based on physical attack stat
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", ClampMax = "1.0", UIMin = "0", UIMax = "1.0"))
	float physicalDamageModifier = 1.0f;

	// Modifies attack output based on the ki stat
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", ClampMax = "1.0", UIMin = "0", UIMax = "1.0"))
	float kiDamageModifier = 0.0f;

	// Modifies attack output based on the arcane stat
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", ClampMax = "1.0", UIMin = "0", UIMax = "1.0"))
	float arcaneDamageModifier = 0.0f;
};

// Copyright © 2025, Nathan Adotey. All Rights Reserved.