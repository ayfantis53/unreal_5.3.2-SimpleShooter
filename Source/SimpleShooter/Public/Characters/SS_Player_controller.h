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
#include "GameFramework/PlayerController.h"
#include "SS_Player_controller.generated.h"


class AActor;
class SSS_Widget_win_screen;
class SSS_Widget_lose_screen;

/**
 *	Player controller for Shooter player in game 
 */
UCLASS()
class SIMPLESHOOTER_API ASS_Player_controller : public APlayerController
{
	GENERATED_BODY()

public:
	/// @brief Handle win/lose condition.
	/// @param end_game_focus actor to view with camera.
	/// @param b_is_winner    true if this controller is on winning team.
	auto GameHasEnded(AActor* end_game_focus = nullptr, bool b_is_winner = false) -> void override;
	
protected:
	/// @brief Called when the game starts or when spawned.
	auto BeginPlay() -> void override;

private:
	/// @brief prints the win message to player HUD.
	auto set_up_win_widget() -> void;

	/// @brief prints the losing message to player HUD.
	auto set_up_lose_widget() -> void;
	
	/* ------------------ TIMER PROPERTIES ------------------ */

	/// @brief Timer allowing us to trigger game retart based on elapsed time.
	FTimerHandle restart_timer_;

	/// @brief time to count down from before game restarts.
	float restart_delay_{ 5.f };

	/* ---------------------- WIDGETS ----------------------- */

	//// GAME WIN ////

	/// @brief ptr to widget that holds the win game widget.
	TSharedPtr<SWidget> win_game_widget_container_;

	/// @brief Text widget that appears if character wins game.
	TSharedPtr<SSS_Widget_win_screen> win_screen_ref_;
	
	//// GAME LOSE ////

	/// @brief ptr to widget that holds the lose game widget.
	TSharedPtr<SWidget> lose_game_widget_container_;

	/// @brief Text widget that appears if character loses game.
	TSharedPtr<SSS_Widget_lose_screen> lose_screen_ref_;

	/* ----------------------- TESTING ---------------------- */

	/// @brief Test classes to unit test this Player Controller.
	friend class Player_controller_test;
	
	/// @brief Test classes to function test this Player Controller.
	friend class ASS_functional_test_base;
	friend class ASS_functional_test_controller;
	friend class ASS_functional_test_lose;
	friend class ASS_functional_test_player;
};
