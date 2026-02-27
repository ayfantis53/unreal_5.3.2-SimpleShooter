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
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "SS_Bt_service_player_location.generated.h"


/**
 * 	Task for Enemy AI Blackboard to set location of player so enemies know where to attack to
 */
UCLASS()
class SIMPLESHOOTER_API USS_Bt_service_player_location : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	/// @brief Sets Name of BlackBoard Node.
	USS_Bt_service_player_location();

protected:
	/// @brief Tick function this function should be considered as const (don't modify state of object) if node is not instanced!
	/// @param owner_comp    The behavior tree owner of this node.
	/// @param node_memory   The instance memory of the current node.
	/// @param delta_seconds DeltaTime since last call.
	auto TickNode(UBehaviorTreeComponent& owner_comp, uint8* node_memory, float delta_seconds) -> void override;
};
