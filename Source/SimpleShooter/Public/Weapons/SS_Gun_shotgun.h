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
#include "Weapons/SS_Gun_base.h"
#include "SS_Gun_shotgun.generated.h"


/**
 *	Shotgun weapon 
 */
UCLASS()
class SIMPLESHOOTER_API ASS_Gun_shotgun : public ASS_Gun_base
{
	GENERATED_BODY()

public:
	/// @brief Sets default values for this actor's properties.
	ASS_Gun_shotgun();

protected:
	/// @brief Use Constructor helpers to populate all properties.
	auto setup_paths() -> void override;

private:
	/* --------------------- COMPONENTS --------------------- */

	//// PATHS TO MESH COMPONENTS ////

	/// @brief path to shotgun's skeletal mesh in Content folder.
	FString shotgun_skeleton_path_{ "SkeletalMesh'/Game/Weapons/SkeletalMeshes/SK_Shotgun.SK_Shotgun'" };

	/* ---------------------- EFFECTS ----------------------- */

	//// PATHS TO SOUND FX ////

	/// @brief path to shotgun's muzzle sound cue file in Content folder.
	FString muzzle_sound_path_{ "SoundCue'/Game/Weapons/FX/Sounds/Sniper/A_Sniper_Cue.A_Sniper_Cue'" };

	/// @brief path to shotgun's bullet impact sound cue file in Content folder.
	FString impact_sound_path_{ "SoundCue'/Game/Weapons/FX/Sounds/Rifle/A_Rifle_Impact_Cue.A_Rifle_Impact_Cue'" };

	//// PATHS TO PARTICLE FX ////	
	
	/// @brief path to shotgun's flash particles fx file in Content folder.
	FString muzzle_flash_path_{ "ParticleSystem'/Game/AssetPacks/ParagonWraith/FX/Particles/Abilities/Drone/FX/P_Wraith_Drone_Fire.P_Wraith_Drone_Fire'" };

	/// @brief path to shotgun's impact particles fx file in Content folder.
	FString bullet_impact_path_{ "ParticleSystem'/Game/AssetPacks/ParagonWraith/FX/Particles/Abilities/ScopedShot/FX/P_Wraith_Sniper_HitWorld.P_Wraith_Sniper_HitWorld'" };

	/* ----------------------- TESTING ---------------------- */
	
	/// @brief Test classes to unit test this Actor.
	friend class Gun_shotgun_test;
};
