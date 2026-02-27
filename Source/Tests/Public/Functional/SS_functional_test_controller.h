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
#include "SS_functional_test_controller.generated.h"


/**
 *  Test the Player Controller in the game
 */
UCLASS()
class TESTS_API ASS_functional_test_controller : public ASS_functional_test_base
{
	GENERATED_BODY()
	
public:
	/// @brief Sets default values for this test actor's properties.
	ASS_functional_test_controller();

protected:
	/// @brief Called when the game starts or when spawned.
	virtual auto BeginPlay() -> void override;

private:
	/// @brief Win the game.
	UFUNCTION()
	void end_game_win();

	/// @brief Verify Win game widget displays.
	UFUNCTION()
	void verify_win_widget();

	/// @brief Lose the game.
	UFUNCTION()
	void end_game_lose();

	/// @brief Verify Lose game widget displays.
	UFUNCTION()
	void verify_lose_widget();
};
