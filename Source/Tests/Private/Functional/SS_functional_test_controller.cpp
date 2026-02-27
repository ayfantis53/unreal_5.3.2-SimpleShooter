// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //
#include "Functional/SS_functional_test_controller.h"

#include "Characters/SS_Player_controller.h"
#include "UI/SS_Widget_win_screen.h"
#include "UI/SS_Widget_lose_screen.h"


ASS_functional_test_controller::ASS_functional_test_controller()
{
    wait_delay_  = 2;
    timer_delay_ = 1.f;
}

auto ASS_functional_test_controller::BeginPlay() -> void
{
    Super::BeginPlay();

    test_steps_list_ = {
        "setup",
        "end_game_win",
        "verify_win_widget",
        "wait",
        "end_game_lose",
        "wait",
        "verify_lose_widget",
        "finish_test"
    };
}

auto ASS_functional_test_controller::end_game_win() -> void
{
    // Set game to win.
    bool game_won = true;
    controller_ref_->GameHasEnded(nullptr, game_won);

    progress_test_step();
}

auto ASS_functional_test_controller::verify_win_widget() -> void
{
    // Is Start win widget visible?
    AssertTrue(controller_ref_->win_screen_ref_->GetVisibility() == EVisibility::Visible, "Win Game widget active.");

    progress_test_step();
}

auto ASS_functional_test_controller::end_game_lose() -> void
{
    // Set game to win.
    bool game_won = false;
    controller_ref_->GameHasEnded(nullptr, game_won);

    progress_test_step();
}

auto ASS_functional_test_controller::verify_lose_widget() -> void
{
    // Is End game widget visible?
    AssertTrue(controller_ref_->lose_screen_ref_->GetVisibility() == EVisibility::Visible, "End Game widget active.");

    progress_test_step();
}
