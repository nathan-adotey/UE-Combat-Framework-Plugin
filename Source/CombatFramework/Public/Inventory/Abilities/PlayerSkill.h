// * Copyright © 2025, Nathan Adotey. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/Items/ItemBase.h"
#include "PlayerSkill.generated.h"

UCLASS()
class COMBATFRAMEWORK_API UPlayerSkill : public UItemBase
{
	GENERATED_BODY()

public:
	// * Constructor
	UPlayerSkill();

public:
	// * Plays this montage while the player is on the ground
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill Data")
	TMap<EWeaponCategory, FComboInfo> groundMontage;

	// * Plays this montage while the player is in the air
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill Data")
	TMap<EWeaponCategory, FComboInfo> aerialMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill Data")
	bool bCanPlayOnGround = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill Data")
	bool bCanPlayInAir = false;


	// * MP cost (Mana)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats",
		meta = (
			ClampMin = "0",
			UIMin = "0"
		)
	)
	float manaCost;

	// * HP cost (Health)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats",
		meta = (
			ClampMin = "0",
			UIMin = "0"
		)
	)
	float healthCost;

	// * Accounts the player's strength stat in total damage output
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats",
		meta = (
			ClampMin = "0",
			ClampMax = "1",
			UIMin = "0",
			UIMax = "1"
		)
	)
	float strengthScaling;

	// * Accounts the player's ki stat in total damage output
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats",
		meta = (
			ClampMin = "0",
			ClampMax = "1",
			UIMin = "0",
			UIMax = "1"
		)
	)
	float kiScaling;

	// * Accounts the player's arcane stat in total damage output
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats",
		meta = (
			ClampMin = "0",
			ClampMax = "1",
			UIMin = "0",
			UIMax = "1"
		)
	)
	float arcaneScaling;
};

// * Copyright © 2025, Nathan Adotey. All Rights Reserved.