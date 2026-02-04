// Copyright © 2025, Nathan Adotey. All Rights Reserved.

#pragma once

#include "Data/CStructures.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatSystemAI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGroundAttackAI);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAirAttackAI);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGroundSlamAI);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGroundRushAttackAI);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAerialRushAttackAI);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Abstract, Blueprintable, DefaultToInstanced)
class COMBATFRAMEWORK_API UCombatSystemAI : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Constructor
	UCombatSystemAI();

	// Function delegate which invokes a callback method when a ground attack has been executed
	UPROPERTY(BlueprintAssignable)
	FOnGroundAttackAI OnGroundAttack;

	// Function delegate which invokes a callback method when an aerial attack has been executed
	UPROPERTY(BlueprintAssignable)
	FOnAirAttackAI OnAirAttack;

	// Function delegate which invokes a callback method when a ground slam has been executed
	UPROPERTY(BlueprintAssignable)
	FOnGroundSlamAI OnGroundSlam;

	// Function delegate which invokes a callback method when a ground rush attack has been executed
	UPROPERTY(BlueprintAssignable)
	FOnGroundRushAttackAI OnGroundRushAttack;

	// Function delegate which invokes a callback method when an aerial rush attack has been executed
	UPROPERTY(BlueprintAssignable)
	FOnAerialRushAttackAI OnAerialRushAttack;

public:
	// Static combat data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat System")
	FCombatData combatData;

	// Array of hit reactions (selects a random element on hit while on the ground)
	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<UAnimMontage>> groundHitReactions;

	// Array of hit reactions (selects a random element on hit while in the air)
	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<UAnimMontage>> aerialHitReactions;

	// Knockdown hit reaction
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAnimMontage> knockdownHitReaction;

public:
	UFUNCTION(BlueprintCallable)
	void LightAttack();

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
};

// Copyright © 2025, Nathan Adotey. All Rights Reserved.
