// Copyright © 2025, Nathan Adotey. All Rights Reserved.

#include "Inventory/Inventory.h"

UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = false;

	weaponInventoryCapacity = 0;
	ammoGauge = 5;
}

void UInventory::AddWeaponToInventory(FCombatData weapon)
{
	if (weaponInventory.Num() < weaponInventoryCapacity || (weaponInventoryCapacity == 0))
	{
		FCombatData weaponData = weapon;
		weaponData.inventoryIndex = weaponInventory.Num();
		weaponInventory.Add(weaponData);
		onWeaponAdded.Broadcast(weaponData);
	}
}

void UInventory::RemoveWeaponFromInventory(int inventoryIndex)
{	
	try
	{
		onWeaponRemoved.Broadcast(weaponInventory[inventoryIndex]);
		weaponInventory.RemoveAt(inventoryIndex);
		int i = 0;
		for (i; i < weaponInventory.Num(); i++)
		{
			weaponInventory[i].inventoryIndex = i;
		}
	}
	catch (const std::exception&)  // If an exception is thrown, generate an error log for the editor
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid element"))
	}
}

const int UInventory::GetWeaponInventoryCount()
{
	return weaponInventory.Num();
}

void UInventory::EquipWeapon(const FCombatData newWeapon)
{
	try
	{
		onWeaponUnequipped.Broadcast(currentWeapon);
	}
	catch (const std::exception&) // Throw an exception if the player does not have an equipped weapon
	{
		UE_LOG(LogTemp, Warning, TEXT("NULL weapon data"))
	}
	
	onWeaponEquipped.Broadcast(newWeapon);
	currentWeapon = newWeapon;
}

// Copyright © 2025, Nathan Adotey. All Rights Reserved.