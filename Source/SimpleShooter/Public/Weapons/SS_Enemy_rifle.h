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
#include "SS_Enemy_rifle.generated.h"


/**
 *	Enemy Rifle Weapon  
 */
UCLASS()
class SIMPLESHOOTER_API ASS_Enemy_rifle : public ASS_Gun_base
{
	GENERATED_BODY()
	
	/// @brief Sets default values for this actor's properties.
	ASS_Enemy_rifle();

protected:
	/// @brief Use Constructor helpers to populate all properties.
	auto setup_paths() -> void override;

private:
    /* --------------------- COMPONENTS --------------------- */

    //// PATHS TO MESH COMPONENTS ////

    /// @brief path to rifle's skeletal mesh in Content folder.
	FString rifle_skeleton_path_{ "SkeletalMesh'/Game/Weapons/SkeletalMeshes/SK_Rifle_Enemy.SK_Rifle_Enemy'" };

	/* ---------------------- EFFECTS ----------------------- */

	//// PATHS TO SOUND FX ////

    /// @brief path to rifle's muzzle sound cue file in Content folder.
	FString muzzle_sound_path_{ "SoundCue'/Game/Weapons/FX/Sounds/Rifle/A_RifleShot_Cue.A_RifleShot_Cue'" };

	/// @brief path to rifle's impact sound cue file in Content folder.
	FString impact_sound_path_{ "SoundCue'/Game/Weapons/FX/Sounds/Rifle/A_Rifle_Impact_Cue.A_Rifle_Impact_Cue'" };

    //// PATHS TO PARTICLE FX ////

	/// @brief path to rifle's flash particles fx file in Content folder.
	FString muzzle_flash_path_{ "ParticleSystem'/Game/Weapons/FX/ParticleSystems/P_AssaultRifle_MF.P_AssaultRifle_MF'" };

	/// @brief path to rifle's trail particles fx file in Content folder.
	FString bullet_impact_path_{ "ParticleSystem'/Game/Weapons/FX/ParticleSystems/P_AssaultRifle_IH.P_AssaultRifle_IH'" };

	/// @brief path to rifle's impact particles fx file in Content folder.
	FString bullet_trail_path_{ "ParticleSystem'/Game/Weapons/FX/ParticleSystems/P_AssaultRifle_Trail.P_AssaultRifle_Trail'" };

	/* ----------------------- TESTING ---------------------- */
	
	/// @brief Test classes to unit test this Actor.
	friend class Enemy_rifle_test;
};
