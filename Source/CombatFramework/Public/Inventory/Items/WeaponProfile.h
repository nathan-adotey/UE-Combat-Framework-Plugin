// * Copyright © 2025, Nathan Adotey. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/Items/ItemBase.h"
#include "WeaponProfile.generated.h"

UCLASS()
class COMBATFRAMEWORK_API UWeaponProfile : public UItemBase
{
	GENERATED_BODY()

public:
	UWeaponProfile();

public:
	// * Weapon category
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat Data")
	EWeaponCategory weaponCategory;

	// * Combo sequences
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Data")
	TArray<FComboSchema> attackCombos;

	// * Sprint attack (Light input)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Data")
	FComboInfo lightSprintAttack;

	// * Sprint attack (Heavy input)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Data")
	FComboInfo heavySprintAttack;

	// * Dodge attack (Light input)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Data")
	FComboInfo lightDodgeAttack;

	// * Dodge attack (Heavy input)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Data")
	FComboInfo heavyDodgeAttack;

	// * Physical attack modifier (i.e. light attack combos, physical skills)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats",
		meta = (
			ClampMin = "1",
			ClampMax = "1000",
			UIMin="1",
			UIMax="1000"
		)
	)
	int basePhysicalDamage;

	// * Default scaling for physical damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats",
		meta = (
			ClampMin = "0",
			ClampMax = "2",
			UIMin = "0",
			UIMax = "2"
		)
	)
	float baseStrengthScaling;

	// * Strength scale multiplier per weapon level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats",
		meta = (
			ClampMin = "0",
			ClampMax = "2",
			UIMin = "0",
			UIMax = "2"
			)
	)
	float strengthScalingRate;

	// * Ki attack modifier (i.e. light attack combos, physical skills)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats",
		meta = (
			ClampMin = "0",
			ClampMax = "100",
			UIMin = "0",
			UIMax = "100"
		)
	)
	int baseKiDamage;

	// * Default scaling for ki damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats",
		meta = (
			ClampMin = "0",
			ClampMax = "2",
			UIMin = "0",
			UIMax = "2"
		)
	)
	float kiScaling;

	// * Ki scale multiplier per weapon level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats",
		meta = (
			ClampMin = "0",
			ClampMax = "2",
			UIMin = "0",
			UIMax = "2"
			)
	)
	float kiScalingRate;

	// * Ki attack modifier (i.e. light attack combos, physical skills)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats",
		meta = (
			ClampMin = "0",
			ClampMax = "100",
			UIMin = "0",
			UIMax = "1000"
		)
	)
	int baseArcaneDamage;

	// * Default scaling for ki damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats",
		meta = (
			ClampMin = "0",
			ClampMax = "2",
			UIMin = "0",
			UIMax = "2"
			)
	)
	float basearcaneScaling;

	// * Arcane scale multiplier per weapon level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats",
		meta = (
			ClampMin = "0",
			ClampMax = "2",
			UIMin = "0",
			UIMax = "2"
			)
	)
	float arcaneScalingRate;
};

// * Copyright © 2025, Nathan Adotey. All Rights Reserved.