// * Copyright © 2025, Nathan Adotey. All Rights Reserved.

#pragma once

UENUM(BlueprintType)
enum class EComboType : uint8 { Ground, Aerial };

UENUM(BlueprintType)
enum class EComboInput : uint8 
{ 
	// * Light/normal input
	Light,
	// * Heavy/special input
	Heavy
};

UENUM(BlueprintType)
enum class EWeaponCategory : uint8 { Melee, Sword, Daggers, Scythe, GunSword };

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	Consumable,
	Weapon,
	Skill,
	Ultimate
};

UENUM(BlueprintType)
enum class EDamageImpact : uint8 { None, Light, Normal, Heavy, Projectile, Knockback, Knockdown, LaunchToAir, SlamToGround };
           
UENUM(BlueprintType)
enum class EQuickAccessSlotIndex : uint8
{
	// * Keyboard 1, XBOX: A, PlayStation: Cross
	Slot_1,
	// * Keyboard 2, XBOX: B, PlayStation: Circle
	Slot_2,
	// * Keyboard 3, XBOX: X, PlayStation: Square
	Slot_3,
	// * Keyboard 4, XBOX: Y, PlayStation: Triangle
	Slot_4
};

// * Copyright © 2025, Nathan Adotey. All Rights Reserved.