// * Copyright © 2025, Nathan Adotey. All Rights Reserved.

#include "Inventory/Abilities/PlayerSkill.h"
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
	if ((CanAttack()))
	{
		previousComboInput = currentComboInput;
		currentComboInput = comboInput;

		if (previousComboInput != currentComboInput)
		{
			currentComboCount = 0;
		}

		switch (comboInput)
		{
		case EComboInput::Light:
			PlayAttackMontage(combatData.weaponData->basicAttackCombos[currentComboCount]);
			break;
		case EComboInput::Heavy:
			PlayAttackMontage(combatData.weaponData->heavyAttackCombos[currentComboCount]);
			break;
		default:
			break;
		}
	}
}

void UCombatSystem::DefensiveEvent()
{
	if (CanUseDefensiveEvent())
	{
		ACharacter* playerRef = UGameplayStatics::GetPlayerCharacter(GetOwner(), 0);
		playerRef->PlayAnimMontage(combatData.defensiveAction, 1.0f, "Default");
		OnDefensiveEvent.Broadcast();
	}
}

void UCombatSystem::OverrideAttack(EComboInput comboInput, FComboInfo overrideComboData)
{
	if (CanAttack() && (IsValid(overrideComboData.montage)))
	{
		PlayAttackMontage(overrideComboData);
	}
}

void UCombatSystem::Skill(FComboInfo skillPayload)
{
	if (CanAttack() == true && (IsValid(skillPayload.montage)))
	{
		ResetComboCount();
		ACharacter* playerRef = UGameplayStatics::GetPlayerCharacter(GetOwner(), 0);
		playerRef->PlayAnimMontage(skillPayload.montage, 1.0f, "Default");
		OnGroundAttack.Broadcast(skillPayload);
		UE_LOG(LogTemp, Log, TEXT("Skill event"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid skill parameters"))		
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
	if (IsValid(comboInfo.montage) && (TestComboTag(comboInfo.comboTag) == true))
	{
		ACharacter* playerRef = UGameplayStatics::GetPlayerCharacter(GetOwner(), 0);
		playerRef->PlayAnimMontage(comboInfo.montage, 1.0f, "Default");
		damageImpact = comboInfo.damageImpact;
		currentComboCount++;
		OnGroundAttack.Broadcast(comboInfo);

		if (comboInfo.resetComboCount)
		{
			currentComboCount = 0;
		}
	}
}

bool UCombatSystem::TestComboTag(FName comboTag)
{
	unsigned short int i = 0;
	for (i; i < comboTags.Num(); i++)
	{
		if (comboTags[i] == comboTag)
		{
			return true;
			break;
		}
	}
	return false;
}

// * Copyright © 2025, Nathan Adotey. All Rights Reserved.