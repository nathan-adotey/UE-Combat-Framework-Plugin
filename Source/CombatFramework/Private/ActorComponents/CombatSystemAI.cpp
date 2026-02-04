// Copyright © 2025, Nathan Adotey. All Rights Reserved.

#include "Inventory/Items/WeaponProfile.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"
#include "ActorComponents/CombatSystemAI.h"

UCombatSystemAI::UCombatSystemAI()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCombatSystemAI::LightAttack()
{
	if (CanExecuteNormalAtack())
	{
		try
		{
			ACharacter* characterRef = static_cast<ACharacter*>(GetOwner());
			int attackIndex = UKismetMathLibrary::RandomIntegerInRange(0, (combatData.weaponData->normalAttackCombos.Num() - 1));
			characterRef->PlayAnimMontage(combatData.weaponData->normalAttackCombos[attackIndex].montage);
			OnGroundAttack.Broadcast();
		}
		catch (std::exception ex)
		{
			UE_LOG(LogTemp, Warning, TEXT("Exception thrown while trying to execute an attack"))
		}
	}
}

// Copyright © 2025, Nathan Adotey. All Rights Reserved.