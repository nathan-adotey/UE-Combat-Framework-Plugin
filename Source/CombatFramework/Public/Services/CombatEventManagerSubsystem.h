 // * Copyright © 2025, Nathan Adotey. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "CombatEventManagerSubsystem.generated.h"

UCLASS()
class COMBATFRAMEWORK_API UCombatEventManagerSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))
	float playerHealthPercentage = 1;

	UPROPERTY(BlueprintReadOnly, meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))
	float playerManaPercentage = 1;

	UPROPERTY(BlueprintReadOnly, meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))
	float targetHealthPercentage = 1;

	UPROPERTY(BlueprintReadOnly, meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))
	float targetManaPercentage = 1;

public:
	UFUNCTION(BlueprintCallable)
	void UpdatePlayerHealth(float healthPercentage);

	UFUNCTION(BlueprintCallable)
	void UpdatePlayerMana(float manaPercentage);

	UFUNCTION(BlueprintCallable)
	void UpdateEnemyHealth(float healthPercentage);

	UFUNCTION(BlueprintCallable)
	void UpdateEnemyMana(float manaPercentage);
};

// * Copyright © 2025, Nathan Adotey. All Rights Reserved.