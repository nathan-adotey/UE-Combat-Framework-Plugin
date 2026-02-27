// * Copyright © 2025, Nathan Adotey. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/Items/ItemBase.h"
#include "Firearm.generated.h"

UENUM(BlueprintType)
enum class EFirearmType : uint8
{
	Pistol,
	DualPistols,
	Bow
};

UCLASS()
class COMBATFRAMEWORK_API UFirearm : public UItemBase
{
	GENERATED_BODY()

public:
	UFirearm();

public:
	// * Firearm type - Determines weapon behavior and overlay animation pose
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat Data")
	EFirearmType firearmType;

	// * Overlay anim montage
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat Data")
	TObjectPtr<UAnimMontage> shootAnim;

	// * Fixed damage modifier (Scales with the player's overall level)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat Data")
	int damage;

	// * Primary firearm
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual Properties")
	TObjectPtr<UStaticMesh> primaryWeaponMesh;

	// * Secondary firearm
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual Properties")
	TObjectPtr<UStaticMesh> secondaryWeaponMesh;
};

// * Copyright © 2025, Nathan Adotey. All Rights Reserved.