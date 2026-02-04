// Copyright © 2025, Nathan Adotey. All Rights Reserved.

#pragma once

#include "Data/CStructures.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatSystem.generated.h"

UENUM(BlueprintType)
enum class EInputBehavior : uint8 { Hold, Press, Release };

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGroundAttack);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAirAttack);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGroundSlam);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGroundRushAttack);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAerialRushAttack);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Abstract, Blueprintable, DefaultToInstanced )
class COMBATFRAMEWORK_API UCombatSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Constructor
	UCombatSystem();

	// Function delegate which invokes a callback method when a ground attack has been executed
	UPROPERTY(BlueprintAssignable)
	FOnGroundAttack OnGroundAttack;

	// Function delegate which invokes a callback method when an aerial attack has been executed
	UPROPERTY(BlueprintAssignable)
	FOnAirAttack OnAirAttack;

	// Function delegate which invokes a callback method when a ground slam has been executed
	UPROPERTY(BlueprintAssignable)
	FOnGroundSlam OnGroundSlam;

	// Function delegate which invokes a callback method when a ground rush attack has been executed
	UPROPERTY(BlueprintAssignable)
	FOnGroundRushAttack OnGroundRushAttack;

	// Function delegate which invokes a callback method when an aerial rush attack has been executed
	UPROPERTY(BlueprintAssignable)
	FOnAerialRushAttack OnAerialRushAttack;

public:
	// Static combat data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat System")
	FCombatData combatData;

	// Determines knockback and visual effect parameters when an attack lands
	UPROPERTY(BlueprintReadWrite, Category = "Combat Properties")
	EDamageImpact damageImpact;

	// Ground combo index; defaults to 0 when a different attack type or finisher executes.
	UPROPERTY(BlueprintReadOnly, Category = "Combat Properties")
	int currentGroundComboCount;

	// Air combo index; defaults to 0 when a different attack type or finisher executes.
	UPROPERTY(BlueprintReadOnly, Category = "Combat Properties")
	int currentAirComboCount;

	// Ground combo speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat System")
	float groundComboSpeed;

	// Air combo speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat System")
	float airComboSpeed;

	// Use an aerial homing attack when near an airborne enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat System")
	bool bUseAerialHomingAttack;

protected:
	// Returns TRUE if the player can execute a ground attack combo (Conditions set within the editor)
	UFUNCTION(BlueprintImplementableEvent)
	bool CanExecuteNormalAtack();

	// Returns TRUE if the player can execute an aerial attack combo (Conditions set within the editor)
	UFUNCTION(BlueprintImplementableEvent)
	bool CanExecuteAirAtack();

	// Returns TRUE if the player can execute a ground rush combo (Conditions set within the editor)
	UFUNCTION(BlueprintImplementableEvent)
	bool CanExecuteGroundRushAtack();

	// Returns TRUE if the player can execute an aerial rush combo (Conditions set within the editor)
	UFUNCTION(BlueprintImplementableEvent)
	bool CanExecuteAerialRushAtack();

	// Determines whether a ground finisher will play after a combo. (Editor-specific virtual function)
	UFUNCTION(BlueprintImplementableEvent)
	bool CanPlayGroundFinisher();

	// Determines whether an aerial finisher will play after an air combo. (Editor-specific virtual function)
	UFUNCTION(BlueprintImplementableEvent)
	bool CanPlayAerialFinisher();

	// Determines whether the player should auto-target towards an airborne enemy. (Editor-specific virtual function)
	UFUNCTION(BlueprintImplementableEvent)
	bool CanPlayHomingAttack();

public:
	// Attempt to execute a ground or aerial combo
	UFUNCTION(BlueprintCallable, Category = "Combat System")
	void LightAttack();

	// Use the actor's ground status to launch a target into the air, or perform a ground slam
	UFUNCTION(BlueprintCallable, Category = "Combat System")
	void Trigger();

	// Eecute a ground or aerial rush attack
	UFUNCTION(BlueprintCallable, Category = "Combat System")
	void RushAttack();

	// Reset ground combo count to 0
	UFUNCTION(BlueprintCallable, Category = "Combat System")
	void ResetGroundComboCounter();

	// Reset aerial combo count to 0
	UFUNCTION(BlueprintCallable, Category = "Combat System")
	void ResetAirComboCounter();

protected:
	// Use the owner's velocity (Z-Axis) to determine whether they are in the air or not
	UFUNCTION(BlueprintPure)
	const bool GetAerialStatus();
};

// Copyright © 2025, Nathan Adotey. All Rights Reserved.