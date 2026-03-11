// * Copyright © 2025, Nathan Adotey. All Rights Reserved.

#pragma once

#include "Data/CEnumerators.h"
#include "CStructures.generated.h"

// * --- Forward declarations ---

class UItemBase;
class UWeaponProfile;
class UPlayerSkill;

// * --- Struct declarations

USTRUCT(BlueprintType)
struct FDamageResistances
{
	GENERATED_BODY()

public:
	// * Damage resistance multiplier for physical-based attacks
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.01", UIMax = "1", ClampMin = "0.01", ClampMax = "1"))
	float defense = 0.05f;

	// * Damage resistance multiplier for ki-based attacks
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.01", UIMax = "1", ClampMin = "0.01", ClampMax = "1"))
	float spirit = 0.05f;

	// * Damage resistance multiplier for arcane-based attacks
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.01", UIMax = "1", ClampMin = "0.01", ClampMax = "1"))
	float faith = 0.05f;
};

USTRUCT(BlueprintType)
struct FStatSchema
{
	GENERATED_BODY()

public:
	// * Current weapon level
	UPROPERTY(BlueprintReadOnly,
		meta = (
			ClampMin = "0",
			ClampMax = "200"
		)
	)
	int currentLevel;

	// * Health modifier stat
	UPROPERTY(EditAnywhere, BlueprintReadOnly,
		meta = (
			ClampMin = "0",
			ClampMax = "100",
			UIMin = "0",
			UIMax = "100"
		)
	)
	int health;

	// * Mana modifier
	UPROPERTY(EditAnywhere, BlueprintReadOnly,
		meta = (
			ClampMin = "0",
			ClampMax = "100",
			UIMin = "0",
			UIMax = "100"
		)
	)
	int mana;

	// * Damage modifier
	UPROPERTY(EditAnywhere, BlueprintReadOnly,
		meta = (
			ClampMin = "0",
			ClampMax = "100",
			UIMin = "0",
			UIMax = "100"
		)
	)
	int strength;

	// * Damage modifier
	UPROPERTY(EditAnywhere, BlueprintReadOnly,
		meta = (
			ClampMin = "0",
			ClampMax = "100",
			UIMin = "0",
			UIMax = "100"
		)
	)
	int ki;

	// * Damage modifier
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

	// * Health multiplier
	UPROPERTY(EditAnywhere, BlueprintReadOnly,
		meta = (
			ClampMin = "0.1",
			ClampMax = "100",
			UIMin = "0.1",
			UIMax = "100"
		)
	)
	float healthMultiplier = 1;
};

USTRUCT(BlueprintType)
struct FCombatData
{
	GENERATED_BODY()

public:
	// * Weapon data asset
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWeaponProfile* weaponData;

	// * Current weapon level
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta = (
			ClampMin = "1",
			ClampMax = "10",
			UIMin = "1",
			UIMax = "10"
		)
	)
	int currentLevel = 1;

	// * Auto-generates when a weapon is added to an inventory
	UPROPERTY(BlueprintReadOnly)
	int inventoryIndex;
};

USTRUCT(BlueprintType)
struct FComboInfo
{
	GENERATED_BODY()

public:
	// * Attack montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> montage;

	// * Impact hit yield different results on impact (i.e. knockbacks, normal stuns, knockdowns)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDamageImpact damageImpact = EDamageImpact::Normal;

	// * Modifies attack output based on physical attack stat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "1.0", UIMin = "0", UIMax = "1.0"))
	float physicalDamageModifier = 1.0f;

	// * Modifies attack output based on the ki stat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "1.0", UIMin = "0", UIMax = "1.0"))
	float kiDamageModifier = 1.0f;

	// * Modifies attack output based on the arcane stat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "1.0", UIMin = "0", UIMax = "1.0"))
	float arcaneDamageModifier = 1.0f;

	// * Resets combo count
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool resetComboCount = false;

	bool operator==(const FComboInfo& Other) const
	{
		return montage == Other.montage && damageImpact == Other.damageImpact && physicalDamageModifier == Other.physicalDamageModifier && kiDamageModifier == Other.kiDamageModifier && arcaneDamageModifier == Other.arcaneDamageModifier && resetComboCount == Other.resetComboCount;
	}
};

inline uint32 GetTypeHash(const FComboInfo& Other)
{
	return GetTypeHash(Other.montage) ^ GetTypeHash(Other.damageImpact) ^ GetTypeHash(Other.physicalDamageModifier) ^ GetTypeHash(Other.kiDamageModifier) ^ GetTypeHash(Other.kiDamageModifier) ^ GetTypeHash(Other.arcaneDamageModifier) ^ GetTypeHash(Other.resetComboCount);
}

USTRUCT(BlueprintType)
struct FComboSchema
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FComboInfo, FName> lightGroundCombo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FComboInfo, FName> heavyGroundCombo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FComboInfo, FName> lightAerialCombo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FComboInfo, FName> heavyAerialCombo;
};

// * Copyright © 2025, Nathan Adotey. All Rights Reserved.