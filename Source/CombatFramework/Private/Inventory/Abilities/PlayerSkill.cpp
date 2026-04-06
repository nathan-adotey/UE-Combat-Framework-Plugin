// * Copyright © 2025, Nathan Adotey. All Rights Reserved.

#include "Inventory/Abilities/PlayerSkill.h"

UPlayerSkill::UPlayerSkill()
{
	itemCategory = EItemCategory::Skill;
	
	healthCost = 0.0f;
	manaCost = 10.0f;
	strengthScaling = 1.0f;
	kiScaling = 0.0f;
	arcaneScaling = 0.0f;
}

// * Copyright © 2025, Nathan Adotey. All Rights Reserved.