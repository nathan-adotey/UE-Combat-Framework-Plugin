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
		comboData.Empty();
		comboTag.Empty();

		previousComboInput = currentComboInput;
		currentComboInput = comboInput;

		UpdateComboInfoArrays(comboInput);
		
		if (comboTags.Contains(comboTag[0]) && (IsValid(comboData[0].montage)))
		{
			if ((comboData[0].resetComboCountOnSeperateInput == true) && (currentComboInput != previousComboInput))
			{
				currentComboCount = 0;
				UpdateComboInfoArrays(comboInput);
			}

			if (CanSprintAttack())
			{
				switch (comboInput)
				{
				case EComboInput::Light:
					PlayAttackMontage(combatData.weaponData->lightSprintAttack);
					break;
				case EComboInput::Heavy:
					PlayAttackMontage(combatData.weaponData->heavySprintAttack);
					break;
				default:
					break;
				}
			}
			else if (CanDodgeAttack())
			{
				switch (comboInput)
				{
				case EComboInput::Light:
					PlayAttackMontage(combatData.weaponData->lightDodgeAttack);
					break;
				case EComboInput::Heavy:
					PlayAttackMontage(combatData.weaponData->heavyDodgeAttack);
					break;
				default:
					break;
				}
			}
			else
			{
				PlayAttackMontage(comboData[0]);
			}
		}
	}
}

void UCombatSystem::OverrideAttack(EComboInput comboInput, FComboInfo overrideComboData)
{
	if (CanAttack() && (IsValid(overrideComboData.montage)))
	{
		PlayAttackMontage(overrideComboData);
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

void UCombatSystem::PlayAttackMontage(FComboInfo comboInfo)
{ 
	ACharacter* playerRef = UGameplayStatics::GetPlayerCharacter(GetOwner(), 0);
	playerRef->PlayAnimMontage(comboInfo.montage, 1.0f, "Default");
	damageImpact = comboInfo.damageImpact;
	OnGroundAttack.Broadcast(comboInfo);
	
	if (comboInfo.resetComboCount)
	{
		currentComboCount = 0;
	}
	else
	{
		currentComboCount++;
	}
}

void UCombatSystem::UpdateComboInfoArrays(EComboInput comboInput)
{
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
}

// * Copyright © 2025, Nathan Adotey. All Rights Reserved.