// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //
#include "Components/SS_Character_movement_component.h"


USS_Character_movement_component::USS_Character_movement_component()
{
	// Lets enemy characters be able to move with nav mesh.
	bUseAccelerationForPaths = true;
}
