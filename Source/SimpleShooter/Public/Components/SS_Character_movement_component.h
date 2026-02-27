// ============================================================================== //
//							Unreal Engine version 5.3.2	
// ============================================================================== //
// Simple Shooter
// ____________________________
// Developed by Andrew Yfantis.
// https://github.com/ayfantis53
//
// 2025
// ============================================================================== //
#pragma once

// Unreal headers
#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SS_Character_movement_component.generated.h"


/**
 *	Movement component so enemy character will move on nav mesh
 */
UCLASS()
class SIMPLESHOOTER_API USS_Character_movement_component : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	/// @brief Sets default values for this character's properties.
	USS_Character_movement_component();

	/// @brief Getter for acceleration path since it protected in unreal code.
	FORCEINLINE auto get_acceleration_path() const -> bool { return bUseAccelerationForPaths; } 
};
