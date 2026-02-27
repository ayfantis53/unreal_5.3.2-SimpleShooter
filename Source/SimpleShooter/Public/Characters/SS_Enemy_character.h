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
#include "Characters/SS_Shooter_character.h"
#include "SS_Enemy_character.generated.h"


/**
 * 	Enemies that player will play against (Shooters) 
 */
UCLASS()
class SIMPLESHOOTER_API ASS_Enemy_character : public ASS_Shooter_character
{
	GENERATED_BODY()

public:
	/// @brief Sets default values for this character's properties.
	/// @param ObjectInitializer controls how default values & settings are applied to new objects when creating subobjects.
	ASS_Enemy_character(const FObjectInitializer& ObjectInitializer);

protected:
	/// @brief Called when the game starts or when spawned.
	auto BeginPlay() -> void override;

	/// @brief setup of all constructor helpers to get paths of assets.
	auto setup_character() -> void override;

private:
	/* --------------------- COMPONENTS --------------------- */

	//// PATHS TO MESH COMPONENTS ////
	
	/// @brief path to players skeletal mesh.
	FString enemy_mesh_path_{ "SkeletalMesh'/Game/AssetPacks/ParagonWraith/Characters/Heroes/Wraith/Skins/LunarOps/Meshes/Wraith_LunarOps.Wraith_LunarOps'" };

	/* ----------------------- TESTING ---------------------- */

	/// @brief Test classes to unit test this Character.
	friend class Enemy_character_test;
};
