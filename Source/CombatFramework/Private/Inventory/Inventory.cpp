// * Copyright © 2025, Nathan Adotey. All Rights Reserved.

#include "Inventory/Items/Firearm.h"
#include "Inventory/Inventory.h"

UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	// * Initialize member variables
	weaponInventoryCapacity = 0;
	ammoGauge = 5;
}

void UInventory::AddWeaponToInventory(FCombatData weapon)
{
	// * Add the weapon to the inventory if the inventory capacity is not at its maximum
	if (weaponInventory.Num() < weaponInventoryCapacity || (weaponInventoryCapacity == 0))
	{
		// * Attempt to update the weapon inventory w/index
		weapon.inventoryIndex = weaponInventory.Num();
		weaponInventory.Add(weapon);
		onWeaponAdded.Broadcast(weapon);
	}
}

void UInventory::RemoveWeaponFromInventory(int inventoryIndex)
{	
	onWeaponRemoved.Broadcast(weaponInventory[inventoryIndex]);
	weaponInventory.RemoveAt(inventoryIndex);

	int i = 0;

	for (i; i < weaponInventory.Num(); i++)
	{
		weaponInventory[i].inventoryIndex = i; // * For-loop to update each item's array index after an element's removal
	}
}

const int UInventory::GetWeaponInventoryCount()
{
	return weaponInventory.Num(); // * Number of weapons in the inventory
}

void UInventory::EquipWeapon(const FCombatData newWeapon)
{
	// * Remove current weapon
	onWeaponUnequipped.Broadcast(currentWeapon);

	// * Update the current weapon object & invoke a callback method
	onWeaponEquipped.Broadcast(newWeapon);
	currentWeapon = newWeapon;
}

void UInventory::EquipFirearm(UFirearm* newFirearm)
{
	if (newFirearm)
	{
		// * Update the current firearm object & invoke a callback method
		currentFirearm = newFirearm;
		onFirearmEquipped.Broadcast(currentFirearm);
	}
}

void UInventory::UnequipFirearm()
{
	currentFirearm = NULL;
	onFirearmUnequipped.Broadcast();
}

void UInventory::EquipQuickAccessItem(UItemBase* item, const EQuickAccessSlotIndex targetSlot)
{
	// * --- Add the item to the quick-access inventory
	quickAccessInventory[GetQuickAccessArrayIndex(targetSlot)] = item;
}

void UInventory::RemoveQuickAccessItem(const EQuickAccessSlotIndex targetSlot, bool bRemoveAllItems)
{
	if (bRemoveAllItems)
	{
		// * --- Attempt to clear every item from the quick-access array
		int arrayIndex = 0; // * Loop index & array element

		for (arrayIndex; arrayIndex <= 3; arrayIndex++)
		{
			quickAccessInventory[arrayIndex] = NULL;
		}
	}
	else
	{
		quickAccessInventory[GetQuickAccessArrayIndex(targetSlot)] = NULL;
	}
}

const unsigned short int UInventory::GetQuickAccessArrayIndex(const EQuickAccessSlotIndex targetSlot)
{
	// * --- Attempt to map the gamepad/keyboard input to an element within the quick-access array

	switch (targetSlot)
	{
	case EQuickAccessSlotIndex::Slot_1:
		return 0;
		break;
	case EQuickAccessSlotIndex::Slot_2:
		return 1;
		break;
	case EQuickAccessSlotIndex::Slot_3:
		return 2;
		break;
	case EQuickAccessSlotIndex::Slot_4:
		return 3;
		break;
	default:
		return 0;
		break;
	}
}

// * Copyright © 2025, Nathan Adotey. All Rights Reserved.