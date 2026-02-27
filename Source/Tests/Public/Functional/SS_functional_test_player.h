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
#include "Functional/SS_functional_test_base.h"
#include "SS_functional_test_player.generated.h"


/**
 *  Test the player activating enemies and getting killed by them
 */
UCLASS()
class TESTS_API ASS_functional_test_player : public ASS_functional_test_base
{
	GENERATED_BODY()
	
public:
	/// @brief Sets default values for this test actor's properties.
	ASS_functional_test_player();

protected:
	/// @brief Called when the game starts or when spawned.
	virtual auto BeginPlay() -> void override;

private:
	/// @brief Presses button to move character forward.
	UFUNCTION()
	void move_forward();

	/// @brief Presses button to move character backward.
	UFUNCTION()
	void move_backward();

	/// @brief Presses button to move character right.
	UFUNCTION()
	void move_right();

	/// @brief Presses button to move character left.
	UFUNCTION()
	void move_left();

	/// @brief Stop walking forward.
	UFUNCTION()
	void stop();

	/// @brief Makes character fired weapon.
	UFUNCTION()
	void character_fire();

	/// @brief Verify character moved forward.
	UFUNCTION()
	void verify_moved_forward();

	/// @brief Verify character moved backward.
	UFUNCTION()
	void verify_moved_backward();

	/// @brief Verify character Rotated right.
	UFUNCTION()
	void verify_moved_right();

	/// @brief Verify character Rotated right.
	UFUNCTION()
	void verify_moved_left();

	/// @brief Verify Lose game variables correct.
	UFUNCTION()
	void verify_win_game();

	/* ------------------ ASSERTION MEMBERS ----------------- */
	
	//// MOVEMENT ////

	/// @brief Character's prev position to compare for test.
	FVector char_last_pos_{};
	
	/// @brief Character's current position to compare for test.
	FVector char_curr_pos_{};

	//// ROTATION ////

	/// @brief Character's prev rotation to compare for test.
	FRotator char_last_rot_{};
	
	/// @brief Character's current rotation to compare for test.
	FRotator char_curr_rot_{};
};
