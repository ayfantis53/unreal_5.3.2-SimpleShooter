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
#include "SS_Gun_launcher.generated.h"


/**
 *	Grenade Launcher weapon 
 */
UCLASS()
class SIMPLESHOOTER_API ASS_Gun_launcher : public ASS_Gun_base
{
	GENERATED_BODY()

public:
	/// @brief Sets default values for this actor's properties.
	ASS_Gun_launcher();

protected:
	/// @brief Use Constructor helpers to populate all properties.
	auto setup_paths() -> void override;

private:
	/* --------------------- COMPONENTS --------------------- */

	//// PATHS TO MESH COMPONENTS ////

	/// @brief path to launcher's skeletal mesh in Content folder.
	FString launcher_skeleton_path_{ "SkeletalMesh'/Game/Weapons/SkeletalMeshes/SK_Launcher.SK_Launcher'" };

	/* ---------------------- EFFECTS ----------------------- */

	//// PATHS TO SOUND FX ////

	/// @brief path to launcher's muzzle sound cue file in Content folder.
	FString muzzle_sound_path_{ "SoundCue'/Game/Weapons/FX/Sounds/Launcher/A_Launcher_Cue.A_Launcher_Cue'" };

	//// PATHS TO PARTICLE FX ////

	/// @brief path to launcher's flash particles fx file in Content folder.
	FString muzzle_flash_path_{ "ParticleSystem'/Game/Weapons/FX/ParticleSystems/P_Launcher_MFNew.P_Launcher_MFNew'" };

	/* ----------------------- TESTING ---------------------- */
	
	/// @brief Test classes to unit test this Actor.
	friend class Gun_launcher_test;
};
