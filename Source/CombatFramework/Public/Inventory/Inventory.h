// Copyright © 2025, Nathan Adotey. All Rights Reserved.

#pragma once

#include "Data/CStructures.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

// --- Delegate declarations ---

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponAdded, FCombatData, addedWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponRemoved, FCombatData, removedWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponEquipped, FCombatData, equippedWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponUnequipped, FCombatData, unequippedWeapon);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMBATFRAMEWORK_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:
	// Constructor
	UInventory();

	// Callback method invoked when adding a weapon to the inventory
	UPROPERTY(BlueprintAssignable)
	FOnWeaponAdded onWeaponAdded;

	// Callback method invoked when removing a weapon from the inventory
	UPROPERTY(BlueprintAssignable)
	FOnWeaponRemoved onWeaponRemoved;

	// Callback method invoked when equipping a weapon
	UPROPERTY(BlueprintAssignable)
	FOnWeaponEquipped onWeaponEquipped;

	// Callback method invoked when equipping a weapon
	UPROPERTY(BlueprintAssignable)
	FOnWeaponUnequipped onWeaponUnequipped;

public:
	// Weapon inventory represented as a dynamic array
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCombatData> weaponInventory;

	// Capacity limit for the weapon inventory. A value of "0" indicates no capacity limit.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, 
		meta = (
			UIMin = "0",
			ClampMin = "0"
		)
	)
	int weaponInventoryCapacity;

	// Current weapon
	UPROPERTY(BlueprintReadOnly)
	FCombatData currentWeapon;

public:
	// Add a weapon to the weapon inventory
	UFUNCTION(BlueprintCallable)
	void AddWeaponToInventory(FCombatData weapon);

	// Removes a weapon at a given index
	UFUNCTION(BlueprintCallable)
	void RemoveWeaponFromInventory(int inventoryIndex);

	// Returns the number of weapons within the inventory
	UFUNCTION(BlueprintPure)
	const int GetWeaponInventoryCount();

	// Attempt to equip a weapon
	UFUNCTION(BlueprintCallable)
	void EquipWeapon(const FCombatData newWeapon);
};

// Copyright © 2025, Nathan Adotey. All Rights Reserved.