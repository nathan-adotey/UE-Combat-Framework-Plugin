// * Copyright © 2025, Nathan Adotey. All Rights Reserved.

#pragma once

#include "Data/CStructures.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemBase.generated.h"

UCLASS()
class COMBATFRAMEWORK_API UItemBase : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// * Constructor
	UItemBase();

public:
	// * Item name
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default")
	FName name;

	// * Short item description
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default")
	FName description;

	// * Item category
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default")
	EItemCategory itemCategory;

	// * Currency spent when purchasing an item (Clamped between $0 and $1,000,000)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default", 
		meta = (
			ClampMin = "0",
			ClampMax = "1000000",
			UIMin = "0",
			UIMax = "1000000"
		)
	)
	int purchaseCost;

	// * Currency received when selling an item (Clamped between $0 and $1,000,000)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default",
		meta = (
			ClampMin = "0",
			ClampMax = "1000000",
			UIMin = "0",
			UIMax = "1000000"
			)
	)
	int sellCost;
};

// * Copyright © 2025, Nathan Adotey. All Rights Reserved.