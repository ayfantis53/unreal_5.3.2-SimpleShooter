// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //
#include "Functional/SS_functional_test_player.h"

#include "UI/SS_Widget_win_screen.h"


ASS_functional_test_player::ASS_functional_test_player()
{
    wait_delay_  = 2;
    timer_delay_ = 1.f;
}

auto ASS_functional_test_player::BeginPlay() -> void
{
    Super::BeginPlay();

    test_steps_list_ = {
        "wait",
        "move_forward",
        "verify_moved_forward",
        "stop",
        "move_backward",
        "verify_moved_backward",
        "stop",
        "move_right",
        "verify_moved_right",
        "stop",
        "move_left",
        "verify_moved_left",
        "stop",
        "character_fire",
        "verify_win_game",
        "finish_test"
    };
}

auto ASS_functional_test_player::move_forward() -> void
{   
    // initial character position.
    char_curr_pos_ = player_character_ref_->GetActorLocation();

    // move character forward.
    controller_ref_->InputKey(FInputKeyParams{FKey{"W"}, IE_Pressed, 100.f});

    progress_test_step();
}

auto ASS_functional_test_player::verify_moved_forward() -> void
{   
    // Check if character moved in the positive X.
    char_last_pos_ = char_curr_pos_;
    AssertTrue(player_character_ref_->GetActorLocation().X > char_curr_pos_.X, "Character moved forward");

    progress_test_step();
}

auto ASS_functional_test_player::move_backward() -> void
{   
    // initial character position.
    char_curr_pos_ = player_character_ref_->GetActorLocation();

    // move character backward.
    controller_ref_->InputKey(FInputKeyParams{FKey{"S"}, IE_Pressed, 100.f});

    progress_test_step();
}

auto ASS_functional_test_player::verify_moved_backward() -> void
{   
    // Check if character moved in the negative X.
    char_last_pos_ = char_curr_pos_;
    AssertTrue(player_character_ref_->GetActorLocation().X < char_last_pos_.X, "Character moved backward");

    progress_test_step();
}

auto ASS_functional_test_player::move_right() -> void
{   
    // Change delay between tests since projectile will only exist shortly.
    timer_delay_   = 0.1f;
    char_last_rot_ = player_character_ref_->GetActorRotation();

    // move character forward.
    controller_ref_->InputKey(FInputKeyParams{FKey{"D"}, IE_Pressed, 1.f});

    progress_test_step();
}

auto ASS_functional_test_player::verify_moved_right() -> void
{   
    // Check if character rotated in postive YAW.
    char_last_rot_ = char_curr_rot_;
    AssertTrue(player_character_ref_->GetActorRotation().Yaw > char_last_rot_.Yaw, "Character turned right");

    progress_test_step();
}

auto ASS_functional_test_player::move_left() -> void
{   
    timer_delay_ = 0.3f;
    // move character forward.
    controller_ref_->InputKey(FInputKeyParams{FKey{"A"}, IE_Pressed, 1.f});

    progress_test_step();
}

auto ASS_functional_test_player::verify_moved_left() -> void
{   
    // Check if character rotated in negative YAW.
    AssertTrue(player_character_ref_->GetActorRotation().Yaw < char_last_rot_.Yaw, "Character turned left");

    progress_test_step();
}

auto ASS_functional_test_player::stop() -> void
{   
    timer_delay_ = 1.f;

    // stop character.
    controller_ref_->InputKey(FInputKeyParams{FKey{"W"}, IE_Released, 100.f});
    controller_ref_->InputKey(FInputKeyParams{FKey{"S"}, IE_Released, 100.f});
    controller_ref_->InputKey(FInputKeyParams{FKey{"D"}, IE_Released, 100.f});
    controller_ref_->InputKey(FInputKeyParams{FKey{"A"}, IE_Released, 100.f});

    progress_test_step();
}

auto ASS_functional_test_player::character_fire() -> void
{   
    // Fire character weapon.
    const auto fire_value = FInputActionValue(true);
    do_player_ia(player_character_ref_->shoot_action_, fire_value, input_subsystem_ref_);

    progress_test_step();
}

auto ASS_functional_test_player::verify_win_game() -> void
{
    if (controller_ref_)
    {
        // Is End game widget visible?
        AssertTrue(controller_ref_->win_screen_ref_->GetVisibility() == EVisibility::Visible, "Win Game widget active.");
    }
    else
    {
        abort_test();
    }
    
    progress_test_step();
}
