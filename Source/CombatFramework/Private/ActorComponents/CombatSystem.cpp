// Copyright © 2025, Nathan Adotey. All Rights Reserved.

#include "Inventory/Items/WeaponProfile.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"
#include "ActorComponents/CombatSystem.h"

UCombatSystem::UCombatSystem()
{
	PrimaryComponentTick.bCanEverTick = false;
	groundComboSpeed = 1.0f;
	airComboSpeed = 1.0f;
}

void UCombatSystem::LightAttack()
{
	if (CanExecuteNormalAtack() == true)
	{
		if (currentGroundComboCount < combatData.groundComboLimit)
		{
			// Player reference
			TObjectPtr<ACharacter> playerRef = UGameplayStatics::GetPlayerCharacter(GetOwner(), 0);

			if (CanPlayHomingAttack() && bUseAerialHomingAttack)
			{
				playerRef->PlayAnimMontage(combatData.weaponData->aerialHomingAttack, airComboSpeed);

				// Update combo index
				currentGroundComboCount = 0;
				currentAirComboCount = 0;

				damageImpact = EDamageImpact::Normal;
			}
			else
			{
				// Play attack animation
				playerRef->PlayAnimMontage(combatData.weaponData->normalAttackCombos[currentGroundComboCount].montage, groundComboSpeed);
				
				// Update damage impact
				damageImpact = combatData.weaponData->normalAttackCombos[currentGroundComboCount].damageImpact;

				// Update combo index
				currentGroundComboCount++;
				currentAirComboCount = 0;
			}

			// Invoke a callbak method within the editor
			OnGroundAttack.Broadcast();
			UE_LOG(LogTemp, Display, TEXT("[Combat System]: SUCCESS : Light attack"))
		}
		else if (CanPlayGroundFinisher() == true)
		{
			// Player reference
			ACharacter* playerRef = UGameplayStatics::GetPlayerCharacter(GetOwner(), 0);

			// Play ground finisher
			playerRef->PlayAnimMontage(combatData.weaponData->groundFinisher.montage, groundComboSpeed);

			// Update damage impact
			damageImpact = combatData.weaponData->groundFinisher.damageImpact;

			// Invoke a callbak method within the editor
			OnGroundAttack.Broadcast();
			SET_WARN_COLOR(COLOR_CYAN);
			UE_LOG(LogTemp, Display, TEXT("[Combat System]: SUCCESS : Ground finisher"));
		}
	}
	else if (CanExecuteAirAtack() == true)
	{
		if (currentAirComboCount < combatData.airComboLimit)
		{
			// Player reference
			TObjectPtr<ACharacter> playerRef = UGameplayStatics::GetPlayerCharacter(GetOwner(), 0);

			// Play attack animation
			playerRef->PlayAnimMontage(combatData.weaponData->aerialAttackCombos[currentAirComboCount].montage, airComboSpeed);

			// Update damage impact
			damageImpact = combatData.weaponData->aerialAttackCombos[currentAirComboCount].damageImpact;

			// Update combo index
			currentAirComboCount++;
			currentGroundComboCount = 0;

			// Invoke a callbak method within the editor
			OnAirAttack.Broadcast();

			// Editor log(s)
			UE_LOG(LogTemp, Display, TEXT("[Combat System]: SUCCESS : Light attack"))
		}
		else if (CanPlayAerialFinisher() == true)
		{
			// Player reference
			ACharacter* playerRef = UGameplayStatics::GetPlayerCharacter(GetOwner(), 0);

			// Play ground finisher
			playerRef->PlayAnimMontage(combatData.weaponData->aerialFinisher.montage, airComboSpeed);

			// Update damage impact
			damageImpact = combatData.weaponData->aerialFinisher.damageImpact;

			// Invoke a callbak method within the editor
			OnAirAttack.Broadcast();

			// Editor log(s)
			UE_LOG(LogTemp, Display, TEXT("[Combat System]: SUCCESS : Aerial finisher"));
		}
	}
}

void UCombatSystem::Trigger()
{
	if (CanExecuteNormalAtack() == true)
	{
		// Player reference
		TObjectPtr<ACharacter> playerRef = UGameplayStatics::GetPlayerCharacter(GetOwner(), 0);

		// Play attack animation
		playerRef->PlayAnimMontage(combatData.weaponData->launchAttack.montage, 1.0f);

		// Update damage impact
		damageImpact = combatData.weaponData->launchAttack.damageImpact;

		// Invoke a callbak method within the editor
		OnGroundAttack.Broadcast();

		// Update combo index
		currentGroundComboCount = 0;
		currentAirComboCount = 0;

		// Editor log(s)
		UE_LOG(LogTemp, Log, TEXT("[Combat System]: SUCCESS : Launch attack"))
	}
	else if (CanExecuteAirAtack())
	{
		// Player reference
		TObjectPtr<ACharacter> playerRef = UGameplayStatics::GetPlayerCharacter(GetOwner(), 0);

		// Play attack animation
		playerRef->PlayAnimMontage(combatData.weaponData->groundSlam.montage, 1.0f);

		// Update damage impact
		damageImpact = combatData.weaponData->groundSlam.damageImpact;

		// Invoke a callbak method within the editor
		OnGroundSlam.Broadcast();

		// Update combo index
		currentGroundComboCount = 0;
		currentAirComboCount = 0;

		// Editor log(s)
		UE_LOG(LogTemp, Log, TEXT("[Combat System]: SUCCESS : Ground slam"))
	}
}

void UCombatSystem::RushAttack()
{
	if (CanExecuteGroundRushAtack())
	{
		// Player reference
		TObjectPtr<ACharacter> playerRef = UGameplayStatics::GetPlayerCharacter(GetOwner(), 0);

		// Play attack animation
		playerRef->PlayAnimMontage(combatData.weaponData->groundRush, groundComboSpeed);
		
		// Update combo index
		currentGroundComboCount = 0;
		currentAirComboCount = 0;

		// Invoke a callbak method within the editor
		OnGroundRushAttack.Broadcast();
	}
	else if (CanExecuteAerialRushAtack())
	{
		// Player reference
		TObjectPtr<ACharacter> playerRef = UGameplayStatics::GetPlayerCharacter(GetOwner(), 0);

		// Play attack animation
		playerRef->PlayAnimMontage(combatData.weaponData->aerialRush, airComboSpeed);

		// Update combo index
		currentGroundComboCount = 0;
		currentAirComboCount = 0;

		// Invoke a callbak method within the editor
		OnAerialRushAttack.Broadcast();
	}
}

void UCombatSystem::ResetGroundComboCounter()
{
	currentGroundComboCount = 0;
}

void UCombatSystem::ResetAirComboCounter()
{
	currentAirComboCount = 0;
}

const bool UCombatSystem::GetAerialStatus()
{
	return false;
}

// Copyright © 2025, Nathan Adotey. All Rights Reserved.