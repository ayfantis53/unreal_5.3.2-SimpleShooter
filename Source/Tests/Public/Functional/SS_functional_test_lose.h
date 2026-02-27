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
#include "SS_functional_test_lose.generated.h"


/**
 *  Test the player activating enemies and getting killed by them
 */
UCLASS()
class TESTS_API ASS_functional_test_lose : public ASS_functional_test_base
{
	GENERATED_BODY()
	
public:
	/// @brief Sets default values for this test actor's properties.
	ASS_functional_test_lose();

protected:
	/// @brief Called when the game starts or when spawned.
	virtual auto BeginPlay() -> void override;

private:
	/// @brief Walk forward.
	UFUNCTION()
	void move_forward();

	/// @brief Test Enemy not having a Reaction.
	UFUNCTION()
	void validate_no_enemy_reaction();

	/// @brief Stop walking forward.
	UFUNCTION()
	void stop();

	/// @brief Test Enemy Reaction.
	UFUNCTION()
	void validate_enemy_reaction();

	/// @brief Verify Lose game variables correct.
	UFUNCTION()
	void verify_lose_game();
};
