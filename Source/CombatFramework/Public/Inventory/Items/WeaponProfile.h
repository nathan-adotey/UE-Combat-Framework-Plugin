// Copyright © 2025, Nathan Adotey. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/Items/ItemBase.h"
#include "WeaponProfile.generated.h"

UCLASS()
class COMBATFRAMEWORK_API UWeaponProfile : public UItemBase
{
	GENERATED_BODY()

public:
	// Weapon category
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat Data")
	EWeaponCategory weaponCategory;

	// Ground combo sequences
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Data")
	TArray<FComboInfo> normalAttackCombos;

	// Aerial attack sequences
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Data")
	TArray<FComboInfo> aerialAttackCombos;

	// Execute a ground finisher once the combo cound has reached its limit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Data")
	FComboInfo groundFinisher;

	// Execute an aerial finisher once the combo cound has reached its limit`
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Data")
	FComboInfo aerialFinisher;

	// Launch an enemy into the air
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Data")
	FComboInfo launchAttack;

	// Execute a ground slam from the air
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Data")
	FComboInfo groundSlam;

	// Execute an ultimate attack or transformation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Data")
	TMap<TObjectPtr<UAnimMontage>, EDamageImpact> ultimate;

	// Ground rush
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Data")
	TObjectPtr<UAnimMontage> groundRush;

	// Aerial rush
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Data")
	TObjectPtr<UAnimMontage> aerialRush;

	// Aerial homing attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Data")
	TObjectPtr<UAnimMontage> aerialHomingAttack;

	// Guard - Notify window for perfect blocking & parrying
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Data")
	TObjectPtr<UAnimMontage> guard;

	// Parry
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat Data")
	TObjectPtr<UAnimMontage> parry;

	// Physical attack modifier (i.e. light attack combos, physical skills)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats",
		meta = (
			ClampMin = "0",
			ClampMax = "2",
			UIMin="0",
			UIMax="2"
		)
	)
	float physicalAttackScaling;

	// Growth rate for physical damage on weapon level up
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats",
		meta = (
			ClampMin = "0",
			ClampMax = "1",
			UIMin = "0",
			UIMax = "1"
		)
	)
	float physicalAttackGrowthRate;

	// Ki attack modifier (i.e. light attack combos, physical skills)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats",
		meta = (
			ClampMin = "0",
			ClampMax = "2",
			UIMin = "0",
			UIMax = "2"
		)
	)
	float kiScaling;

	// Growth rate for ki damage on weapon level up
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats",
		meta = (
			ClampMin = "0",
			ClampMax = "1",
			UIMin = "0",
			UIMax = "1"
		)
	)
	float kiGrowthRate;

	// Ki attack modifier (i.e. light attack combos, physical skills)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats",
		meta = (
			ClampMin = "0",
			ClampMax = "2",
			UIMin = "0",
			UIMax = "2"
			)
	)
	float arcaneScaling;

	// Growth rate for ki damage on weapon level up
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats",
		meta = (
			ClampMin = "0",
			ClampMax = "1",
			UIMin = "0",
			UIMax = "1"
			)
	)
	float arcaneGrowthRate;

	// Primary mesh (i.e. Right-handed armaments)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual Properties")
	TObjectPtr<UStaticMesh> primaryWeaponMesh;

	// Secondary mesh (i.e. Left-handed armaments, shields, sheaths, etc)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual Properties")
	TObjectPtr<UStaticMesh> secondaryWeaponMesh;
};

// Copyright © 2025, Nathan Adotey. All Rights Reserved.