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
#include "Weapons/SS_Gun_base.h"
#include "SS_Gun_sniper.generated.h"


/**
 *	Sniper gun weapon 
 */
UCLASS()
class SIMPLESHOOTER_API ASS_Gun_sniper : public ASS_Gun_base
{
	GENERATED_BODY()

public:
	/// @brief Sets default values for this actor's properties.
	ASS_Gun_sniper();

protected:
	/// @brief Use Constructor helpers to populate all properties.
	auto setup_paths() -> void override;

private:
	/* --------------------- COMPONENTS --------------------- */

	//// PATHS TO MESH COMPONENTS ////

	/// @brief path to sniper's skeletal mesh in Content folder.
	FString sniper_skeleton_path_{ "SkeletalMesh'/Game/Weapons/SkeletalMeshes/SK_Sniper.SK_Sniper'" };

	/* ---------------------- EFFECTS ----------------------- */

	//// PATHS TO SOUND FX ////

	/// @brief path to sniper's muzzle sound cue file in Content folder.
	FString muzzle_sound_path_{ "SoundCue'/Game/Weapons/FX/Sounds/Sniper/A_Sniper_Cue.A_Sniper_Cue'" };

	/// @brief path to sniper's impact sound cue file in Content folder.
	FString impact_sound_path_{ "SoundCue'/Game/Weapons/FX/Sounds/Rifle/A_Rifle_Impact_Cue.A_Rifle_Impact_Cue'" };

	//// PATHS TO PARTICLE FX ////

	/// @brief path to sniper's flash particles fx file in Content folder.
	FString muzzle_flash_path_{ "ParticleSystem'/Game/AssetPacks/ParagonWraith/FX/Particles/Abilities/ScopedShot/FX/P_Wraith_Sniper_MuzzleFlash.P_Wraith_Sniper_MuzzleFlash'" };

	/// @brief path to sniper's trail particles fx file in Content folder.
	FString bullet_trail_path_{ "ParticleSystem'/Game/AssetPacks/ParagonWraith/FX/Particles/Abilities/ScopedShot/FX/P_Sniper_Trail_Smoke_Spline.P_Sniper_Trail_Smoke_Spline'" };

	/// @brief path to sniper's impact particles fx file in Content folder.
	FString bullet_impact_path_{ "ParticleSystem'/Game/AssetPacks/ParagonWraith/FX/Particles/Abilities/ScopedShot/FX/P_Wraith_Sniper_HitCharacter.P_Wraith_Sniper_HitCharacter'" };

	/* ----------------------- TESTING ---------------------- */
	
	/// @brief Test classes to unit test this Actor.
	friend class Gun_sniper_test;
};
