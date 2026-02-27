// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //#pragma once

// Unreal headers
#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "SS_Bt_task_clear_value.generated.h"


/**
 * 	Task for Enemy AI Blackboard to tell Blackboard to clear value of selected Blackboard Key
 */
UCLASS()
class SIMPLESHOOTER_API USS_Bt_task_clear_value : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	/// @brief Sets Name of BlackBoard Node.
	USS_Bt_task_clear_value();

protected:
	/// @brief starts this task.
	/// @param  owner_comp  The behavior tree owner of this node.
	/// @param  node_memory The instance memory of the current node.
	/// @return Succeeded, Failed or InProgress.
	auto ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) -> EBTNodeResult::Type override;
};
