// * Copyright © 2025, Nathan Adotey. All Rights Reserved.

#pragma once

#include "Data/CStructures.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

// * --- Delegate declarations ---

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponAdded, FCombatData, addedWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponRemoved, FCombatData, removedWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponEquipped, FCombatData, equippedWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponUnequipped, FCombatData, unequippedWeapon);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMBATFRAMEWORK_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:
	// * Constructor
	UInventory();

	// * Callback method invoked when adding a weapon to the inventory
	UPROPERTY(BlueprintAssignable)
	FOnWeaponAdded onWeaponAdded;

	// * Callback method invoked when removing a weapon from the inventory
	UPROPERTY(BlueprintAssignable)
	FOnWeaponRemoved onWeaponRemoved;

	// * Callback method invoked when equipping a weapon
	UPROPERTY(BlueprintAssignable)
	FOnWeaponEquipped onWeaponEquipped;

	// * Callback method invoked when unequipping a weapon
	UPROPERTY(BlueprintAssignable)
	FOnWeaponUnequipped onWeaponUnequipped;

public:
	// * Weapon inventory represented as an array
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCombatData> weaponInventory;

	
	// * Capacity limit for the weapon inventory. A value of "0" indicates no capacity limit.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, 
		meta = (
			UIMin = "0",
			ClampMin = "0"
		)
	)
	int weaponInventoryCapacity;

	// * Maximum ability points
	UPROPERTY(EditAnywhere, BlueprintReadWrite, 
		meta = (
			UIMin = "0",
			ClampMin = "0"
		)
	)
	int maximumAvilityPoints;

	// * Current ability points
	UPROPERTY(BlueprintReadOnly)
	int currentAbilityPoints;

	/**
	* Quick access inventory represented as an array
	- Comprises of consumables (non-healing items), skills, and other actions
	- Bound to the gamepad's face buttons, or the keyboard's numbers
	- Array accounts for a maximum of 4 elements
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TArray<UItemBase*> quickAccessInventory;

	// * Current weapon
	UPROPERTY(BlueprintReadOnly)
	FCombatData currentWeapon;

public:
	// * Add a weapon to the weapon inventory
	UFUNCTION(BlueprintCallable)
	void AddWeaponToInventory(FCombatData weapon);
	
	/**
	Remove a weapon from the inventory
	- Use an index (integer) to locate an individual element from the weapon inventory array
	- Re-sorts each remaining weapon's inventory index once a weapon exits the array
	- Invokes a callback method which broadcasts the deleted weapon
	*/
	UFUNCTION(BlueprintCallable)
	void RemoveWeaponFromInventory(int inventoryIndex);

	// * Returns the number of weapons within the inventory (integer)
	UFUNCTION(BlueprintPure)
	const int GetWeaponInventoryCount();

	// * Attempt to equip a weapon
	UFUNCTION(BlueprintCallable)
	void EquipWeapon(const FCombatData newWeapon);

	/**
	Equips an item for the quick-access management
	- TObjectPtr<UItemBase> item: Item the player chooses to equip (if valid)
	- Prevents the quick access inventory from exceeding four elements
	*/
	UFUNCTION(BlueprintCallable)
	void EquipQuickAccessItem(UItemBase* item, const EQuickAccessSlotIndex targetSlot);

	/**
	Removes an item from the quick-access inventory
	- bool bRemoveAllItems: Removes every item from the quick-access array
	- Empty array element are represented as NULL
	*/
	UFUNCTION(BlueprintCallable)
	void RemoveQuickAccessItem(const EQuickAccessSlotIndex targetSlot, bool bRemoveAllItems);

private:
	// * The return value represents an array element's index mapped to a specific button input
	const unsigned short int GetQuickAccessArrayIndex(const EQuickAccessSlotIndex targetSlot);
};

// * Copyright © 2025, Nathan Adotey. All Rights Reserved.