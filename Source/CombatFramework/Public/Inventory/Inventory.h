// Copyright © 2025, Nathan Adotey. All Rights Reserved.

#pragma once

#include "Data/CStructures.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

class UFirearm;

// --- Delegate declarations ---

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponAdded, FCombatData, addedWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponRemoved, FCombatData, removedWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponEquipped, FCombatData, equippedWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponUnequipped, FCombatData, unequippedWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFirearmEquipped, UFirearm*, newFirearm);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFirearmUnequipped);

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

	// Callback method invoked when unequipping a weapon
	UPROPERTY(BlueprintAssignable)
	FOnWeaponUnequipped onWeaponUnequipped;

	// Callback method invoked when equipping a firearm
	UPROPERTY(BlueprintAssignable)
	FOnFirearmEquipped onFirearmEquipped;

	// Callback method invoked when unequipping a firearm
	UPROPERTY(BlueprintAssignable)
	FOnFirearmUnequipped onFirearmUnequipped;

public:
	// Weapon inventory represented as an array
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

	// Current firearm
	UPROPERTY(BlueprintReadOnly)
	UFirearm* currentFirearm;

	/** 
	Current firearm's ammo capacity:
	- Ammo is not a finite resource (i.e. Ammo doesnt need to be purchased, nor aquired to refill the firearm's gauge)
	- The player has an opportunity to refill ammo when applying damage  
	- Damage is calculated based on the player's current level and bypassed all damage resistances
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		meta = (
			UIMin = "0",
			ClampMin = "0"
			)
	)
	int ammoGauge;

public:
	// Add a weapon to the weapon inventory
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

	// Returns the number of weapons within the inventory (integer)
	UFUNCTION(BlueprintPure)
	const int GetWeaponInventoryCount();

	// Attempt to equip a weapon
	UFUNCTION(BlueprintCallable)
	void EquipWeapon(const FCombatData newWeapon);

	// Equip a new firearm
	void EquipFirearm(UFirearm* newFirearm);

	// Unequip firearm (if valid)
	void UnequipFirearm();
};

// Copyright © 2025, Nathan Adotey. All Rights Reserved.