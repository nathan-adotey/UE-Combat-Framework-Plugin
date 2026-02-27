// * Copyright © 2025, Nathan Adotey. All Rights Reserved.

#include "Inventory/Items/WeaponProfile.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"
#include "ActorComponents/CombatSystem.h"

UCombatSystem::UCombatSystem()
{
	PrimaryComponentTick.bCanEverTick = false;
	currentComboCount = 0;
	comboTags.Add("Default");
}

void UCombatSystem::Attack(EComboInput comboInput)
{
	if (CanAttack() == true)
	{
		TObjectPtr<ACharacter> playerRef = UGameplayStatics::GetPlayerCharacter(GetOwner(), 0);
		TArray<FComboInfo> comboData;
		TArray<FName> comboTag;
		comboData.Empty();
		comboTag.Empty();
		
		switch (comboInput)
		{
		case EComboInput::Light:
			if (GetAerialStatus())
			{
				combatData.weaponData->attackCombos[currentComboCount].lightAerialCombo.GenerateKeyArray(comboData);
				combatData.weaponData->attackCombos[currentComboCount].lightAerialCombo.GenerateValueArray(comboTag);
			}
			else
			{
				combatData.weaponData->attackCombos[currentComboCount].lightGroundCombo.GenerateKeyArray(comboData);
				combatData.weaponData->attackCombos[currentComboCount].lightGroundCombo.GenerateValueArray(comboTag);		
			}
			
			break;
		case EComboInput::Heavy:
			if (GetAerialStatus())
			{
				combatData.weaponData->attackCombos[currentComboCount].heavyAerialCombo.GenerateKeyArray(comboData);
				combatData.weaponData->attackCombos[currentComboCount].heavyAerialCombo.GenerateValueArray(comboTag);
			}
			else
			{
				combatData.weaponData->attackCombos[currentComboCount].heavyGroundCombo.GenerateKeyArray(comboData);
				combatData.weaponData->attackCombos[currentComboCount].heavyGroundCombo.GenerateValueArray(comboTag);
			}
			break;
		default:
			break;
		}

		if (comboTags.Contains(comboTag[0]))
		{
			try
			{
				playerRef->PlayAnimMontage(comboData[0].montage, 1.0f);
				OnGroundAttack.Broadcast();
				damageImpact = comboData[0].damageImpact;

				if (comboData[0].resetComboCount == true)
				{
					currentComboCount = 0;
				}
				else
				{
					currentComboCount++;
				}
			}
			catch (const std::exception&)
			{
				UE_LOG(LogTemp, Warning, TEXT("Could not perform attack: Invoked an array element outside of its bounds"))
			}
		}
	}
}

void UCombatSystem::OverrideAttack(EComboInput comboInput, FComboInfo overrideComboData, bool bResetComboCount, bool bIncreaseComboCount)
{
	if (CanAttack())
	{
		try
		{
			ACharacter* playerRef = UGameplayStatics::GetPlayerCharacter(GetOwner(), 0);
			playerRef->PlayAnimMontage(overrideComboData.montage, 1.0f);
			damageImpact = overrideComboData.damageImpact;
			OnGroundAttack.Broadcast();
			if (bIncreaseComboCount) { currentComboCount++; }
		}
		catch (const std::exception&)
		{
			UE_LOG(LogTemp, Warning, TEXT("Exception thrown while attempting to ovcerride an attack"))
		}
	}
}

void UCombatSystem::ResetComboCount()
{
	currentComboCount = 0;
}

const int UCombatSystem::GetCurrentComboCount()
{
	return static_cast<int>(currentComboCount);
}

// * Copyright © 2025, Nathan Adotey. All Rights Reserved.