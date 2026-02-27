// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //
#include "AI/SS_Bt_task_shoot.h"
#include "Characters/SS_Shooter_character.h"

// Unreal headers.
#include "AIController.h"


USS_Bt_task_shoot::USS_Bt_task_shoot()
{
	NodeName = TEXT("Enemy Shoot");
}

auto USS_Bt_task_shoot::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) -> EBTNodeResult::Type
{
	Super::ExecuteTask(owner_comp, node_memory);

	// There doesnt exists a enemy controller.
	if (owner_comp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	// Theres no enemy characters.
	ASS_Shooter_character* enemy_character = Cast<ASS_Shooter_character>(owner_comp.GetAIOwner()->GetPawn());
	if (enemy_character == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	// Make enemy aim before shooting.
	enemy_character->set_aiming(true);
	enemy_character->shoot();

	return EBTNodeResult::Succeeded;
}
