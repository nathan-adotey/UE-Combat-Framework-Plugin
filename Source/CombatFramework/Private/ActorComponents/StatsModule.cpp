// * Copyright © 2025, Nathan Adotey. All Rights Reserved.

#include "Inventory/Items/WeaponProfile.h"
#include "Kismet/KismetMathLibrary.h"
#include "ActorComponents/StatsModule.h"

UStatsModule::UStatsModule()
{
	
}

const float UStatsModule::CalculateMaximumHealth()
{
	float f_Health = static_cast<float>(playerStats.health);
	if (f_Health <= 25)
	{
		return playerStats.healthMultiplier * (UKismetMathLibrary::Round(300 + (500 * ((f_Health - 1) / 24))));
	}
	else if (f_Health > 25 && (f_Health <= 40))
	{
		return playerStats.healthMultiplier * (UKismetMathLibrary::Round(800 + (650 * ((f_Health - 25) / 15))));
	}
	else if (f_Health > 40 && (f_Health <= 60))
	{
		return playerStats.healthMultiplier * (UKismetMathLibrary::Round(1450 + (450 * (1 - (1 - (f_Health - 40) / 20)))));
	}
	else
	{
		return playerStats.healthMultiplier * (UKismetMathLibrary::Round(1900 + (200 * (1 - (1 - (f_Health - 60) / 39)))));
	}
}

const float UStatsModule::CalculateMaximumMana()
{
	float f_mana = static_cast<float>(playerStats.mana);
	if (f_mana <= 15)
	{
		return (UKismetMathLibrary::Round(50 + (45 * ((f_mana - 1) / 14))));
	}
	else if (f_mana > 15 && (f_mana <= 35))
	{
		return (UKismetMathLibrary::Round(95 + (105 * ((f_mana - 15) / 20))));
	}
	else if (f_mana > 35 && (f_mana <= 60))
	{
		return (UKismetMathLibrary::Round(200 + (150 * (1 - (1 - (f_mana - 35) / 25)))));
	}
	else
	{
		return (UKismetMathLibrary::Round(350 + (100 * ((f_mana - 60) / 39))));
	}
}

void UStatsModule::InitializeStats(const bool bHeal)
{
	maximumHealth = CalculateMaximumHealth();
	maximumMana = CalculateMaximumMana();

	if (bUseTestStats)
	{
		playerStats = testStats;
	}
	else
	{
		playerStats.currentLevel = (playerStats.health + playerStats.mana + playerStats.strength + playerStats.ki + playerStats.arcane);
	}

	if (bHeal)
	{
		RecoverAllStats();
	}
}

void UStatsModule::RecoverAllStats()
{
	currentHealth = CalculateMaximumHealth();
	currentMana = maximumMana;
	OnHealthModified.Broadcast(1.0f);
	OnManaModified.Broadcast(1.0f);
}

const float UStatsModule::GetCurrentHealthPercentage()
{
	return currentHealth / CalculateMaximumHealth();
}

const float UStatsModule::GetCurrentManaPercentage()
{
	return currentMana / CalculateMaximumMana();
}

void UStatsModule::RestoreHealth(const float amount)
{
	currentHealth += amount;
	OnHealthModified.Broadcast(currentHealth / maximumHealth); 
}

void UStatsModule::DrainHealth(const float amount)
{
	currentHealth -= amount;

	if (currentHealth < 1.0f)
	{
		currentHealth = 0.0f;
		OnCharacterDeath.Broadcast();
	}

	OnHealthModified.Broadcast(currentHealth / maximumHealth);
}

void UStatsModule::RestoreMana(const float amount)
{
	currentMana += amount;
	if (currentMana > maximumMana)
	{
		currentMana = CalculateMaximumMana();
	}
	OnManaModified.Broadcast(currentMana / maximumMana);
}

void UStatsModule::DrainMana(const float amount)
{
	currentMana = UKismetMathLibrary::Clamp(currentMana - amount, 0, maximumMana);
	OnManaModified.Broadcast(currentMana / maximumMana);
}

const float UStatsModule::CalculatePhysicalWeaponDamage(FCombatData combatProfile)
{
	float weaponDamage = combatProfile.weaponData->basePhysicalDamage * (combatProfile.weaponData->baseStrengthScaling + ((combatProfile.weaponData->strengthScalingRate * combatProfile.currentLevel)));
	float f_stat = static_cast<float>(playerStats.strength);
	

	// Use linear interpolation to apply stat caps
	if (f_stat <= 30.0)
	{
		float strengthScaling = ((f_stat) / (30.0)) * 0.30;
		return weaponDamage * strengthScaling;
	}
	else if (f_stat > 30.0 && (f_stat <= 50.0))
	{
		float strengthScaling = 0.30 + (((f_stat - 31.0) / (50.0 - 31.0)) * (0.60 - 0.30));
		return weaponDamage * strengthScaling;
	}
	else if (f_stat > 50.0 && (f_stat <= 80.0))
	{
		float strengthScaling = 0.70 + (((f_stat - 51.0) / (80.0 - 51.0)) * (0.90 - 0.70));
		return weaponDamage * strengthScaling;
	}
	else
	{
		float strengthScaling = 0.91 + (((f_stat - 81.0) / (100.0 - 81.0)) * (0.95 - 0.91));
		return weaponDamage * strengthScaling;
	}
}

const float UStatsModule::CalculateKiWeaponDamage(FCombatData combatProfile)
{
	float weaponDamage = combatProfile.weaponData->baseKiDamage + (combatProfile.weaponData->kiScalingRate * combatProfile.currentLevel);
	float f_stat = static_cast<float>(playerStats.ki);

	if (f_stat <= 30.0)
	{
		float kiScaling = ((f_stat) / (30.0)) * 0.30;
		return weaponDamage * kiScaling;
	}
	else if (f_stat > 30.0 && (f_stat <= 50.0))
	{
		float kiScaling = 0.30 + (((f_stat - 31.0) / (50.0 - 31.0)) * (0.60 - 0.30));
		return weaponDamage * kiScaling;
	}
	else if (f_stat > 50.0 && (f_stat <= 80.0))
	{
		float kiScaling = 0.70 + (((f_stat - 51.0) / (80.0 - 51.0)) * (0.90 - 0.70));
		return weaponDamage * kiScaling;
	}
	else
	{
		float kiScaling = 0.91 + (((f_stat - 81.0) / (100.0 - 81.0)) * (0.95 - 0.91));
		return weaponDamage * kiScaling;
	}
}

const float UStatsModule::CalculateArcaneWeaponDamage(FCombatData combatProfile)
{
	float weaponDamage = combatProfile.weaponData->baseArcaneDamage + (combatProfile.weaponData->arcaneScalingRate * combatProfile.currentLevel);
	float f_stat = static_cast<float>(playerStats.arcane);

	if (f_stat <= 30.0)
	{
		float arcaneScaling = ((f_stat) / (30.0)) * 0.30;
		return weaponDamage * arcaneScaling;
	}
	else if (f_stat > 30.0 && (f_stat <= 50.0))
	{
		float arcaneScaling = 0.30 + (((f_stat - 31.0) / (50.0 - 31.0)) * (0.60 - 0.30));
		return weaponDamage * arcaneScaling;
	}
	else if (f_stat > 50.0 && (f_stat <= 80.0))
	{
		float arcaneScaling = 0.70 + (((f_stat - 51.0) / (80.0 - 51.0)) * (0.90 - 0.70));
		return weaponDamage * arcaneScaling;
	}
	else
	{
		float arcaneScaling = 0.91 + (((f_stat - 81.0) / (100.0 - 81.0)) * (0.95 - 0.91));
		return weaponDamage * arcaneScaling;
	}
}

// * Copyright © 2025, Nathan Adotey. All Rights Reserved.