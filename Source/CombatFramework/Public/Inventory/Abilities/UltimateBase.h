
#pragma once

#include "Inventory/Items/ItemBase.h"
#include "CoreMinimal.h"
#include "UltimateBase.generated.h"

UENUM(BlueprintType)
enum class EUltimateType : uint8
{
	Attack,
	Transformation,
	Summon,
	Domain
};

UCLASS()
class COMBATFRAMEWORK_API UUltimateBase : public UItemBase
{
	GENERATED_BODY()

public:
	// * Constructor
	UUltimateBase();
};