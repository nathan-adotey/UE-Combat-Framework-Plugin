// * Copyright © 2025, Nathan Adotey. All Rights Reserved.

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
		return (UKismetMathLibrary::Round(300 + (500 * ((f_Health - 1) / 24))));
	}
	else if (f_Health > 25 && (f_Health <= 40))
	{
		return (UKismetMathLibrary::Round(800 + (650 * ((f_Health - 25) / 15))));
	}
	else if (f_Health > 40 && (f_Health <= 60))
	{
		return (UKismetMathLibrary::Round(1450 + (450 * (1 - (1 - (f_Health - 40) / 20)))));
	}
	else
	{
		return (UKismetMathLibrary::Round(1900 + (200 * (1 - (1 - (f_Health - 60) / 39)))));
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
	playerStats.currentLevel = (playerStats.health + playerStats.mana + playerStats.strength + playerStats.ki + playerStats.arcane);
	if (bHeal)
	{
		RecoverAllStats();
	}
}

void UStatsModule::RecoverAllStats()
{
	currentHealth = maximumHealth;
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
	currentHealth = UKismetMathLibrary::Clamp(currentHealth + amount, 0, maximumHealth);
	OnHealthModified.Broadcast(currentHealth / maximumHealth); 
}

void UStatsModule::DrainHealth(const float amount)
{
	currentHealth = UKismetMathLibrary::Clamp(currentHealth - amount, 0, maximumHealth);

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

// * Copyright © 2025, Nathan Adotey. All Rights Reserved.