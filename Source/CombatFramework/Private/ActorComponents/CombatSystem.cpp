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

		if (comboTags.Contains(comboTag[0]) && (IsValid(comboData[0].montage)))
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
	}
}

void UCombatSystem::OverrideAttack(EComboInput comboInput, FComboInfo overrideComboData, bool bResetComboCount, bool bIncreaseComboCount)
{
	if (CanAttack() && (IsValid(overrideComboData.montage)))
	{
		ACharacter* playerRef = UGameplayStatics::GetPlayerCharacter(GetOwner(), 0);
		playerRef->PlayAnimMontage(overrideComboData.montage, 1.0f);
		damageImpact = overrideComboData.damageImpact;
		OnGroundAttack.Broadcast();
		if (bIncreaseComboCount) { currentComboCount++; }
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

const FTransform UCombatSystem::CalculateMotionWarpTargetTransform(AActor* targetActor)
{
	return FTransform();
}

// * Copyright © 2025, Nathan Adotey. All Rights Reserved.