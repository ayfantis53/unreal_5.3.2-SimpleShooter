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
#include "AIController.h"
#include "SS_Enemy_ai_controller.generated.h"


class UBehaviorTree;

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ASS_Enemy_ai_controller : public AAIController
{
	GENERATED_BODY()
	
public:
	/// @brief Sets Name of BlackBoard Node.
	ASS_Enemy_ai_controller();

	/// @brief Called every frame.
	/// @param delta_time Time taken between the frames of the gameplay can differ.
	auto Tick(float delta_time) -> void override;

	/// @brief tells us if this actor is dead.
	/// @return bool if player died.
	auto b_is_dead() const -> bool;

protected:
	/// @brief Called when the game starts or when spawned.
	auto BeginPlay() -> void override;

private:
	/* -------------------- BEHAVIOR TREE ------------------- */

	//// POINTERS ////

	/// @brief Blackboard Behavior Tree for our AI movement and actions.
	UPROPERTY(VisibleAnywhere)
	UBehaviorTree* ai_behavior_tree_;

	//// PATHS ////
	
	/// @brief Path to Enemy Character AI Behavior Tree.
	FString behavior_tree_path_{ "BehaviorTree'/Game/AssetPacks/ParagonWraith/Characters/Heroes/Wraith/BT_Enemy_character_AI.BT_Enemy_character_AI'" };

	/* ------------------- ENEMY BEHAVIOR ------------------- */

	/// @brief radius of how far we need to be before we interact with whatever is in this radius.
	float acceptance_radius_{ 200.f };
};
