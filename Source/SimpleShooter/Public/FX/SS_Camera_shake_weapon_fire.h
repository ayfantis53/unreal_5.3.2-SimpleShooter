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
#include "LegacyCameraShake.h"
#include "SS_Camera_shake_weapon_fire.generated.h"


/**
 *	Camera Shake Effect for when a gun is fired by player
 */
UCLASS()
class SIMPLESHOOTER_API USS_Camera_shake_weapon_fire : public ULegacyCameraShake
{
	GENERATED_BODY()
	
public:
	/// @brief Sets default values for this actor's properties.
	USS_Camera_shake_weapon_fire();
};
