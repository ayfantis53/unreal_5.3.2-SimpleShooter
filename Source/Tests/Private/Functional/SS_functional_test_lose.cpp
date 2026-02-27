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
#include "Functional/SS_functional_test_lose.h"

#include "UI/SS_Widget_lose_screen.h"


ASS_functional_test_lose::ASS_functional_test_lose()
{
    wait_delay_  = 2;
    timer_delay_ = 1.f;
}

auto ASS_functional_test_lose::BeginPlay() -> void
{
    Super::BeginPlay();

    test_steps_list_ = {
        "wait",
        "validate_no_enemy_reaction",
        "move_forward",
        "wait",
        "wait",
        "validate_enemy_reaction",
        "stop",
        "wait",
        "verify_lose_game",
        "finish_test"
    };
}

auto ASS_functional_test_lose::move_forward() -> void
{
    // move player forward.
    controller_ref_->InputKey(FInputKeyParams{FKey{"W"}, IE_Pressed, 100.f});

    progress_test_step();
}

auto ASS_functional_test_lose::validate_no_enemy_reaction() -> void
{
    TArray<AActor*> enemies{};
	UGameplayStatics::GetAllActorsOfClass(this, ASS_Enemy_character::StaticClass(), enemies);

    for (auto& actor : enemies)
	{
        auto enemy = Cast<ASS_Enemy_character>(actor);
		AssertFalse(enemy->b_aiming_,              "Enemy is NOT aiming.");
        AssertFalse(enemy->b_fire_button_pressed_, "Enemy is NOT firing.");
	}

    progress_test_step();
}

auto ASS_functional_test_lose::stop() -> void
{
    controller_ref_->InputKey(FInputKeyParams{FKey{"W"}, IE_Released, 100.f});

    progress_test_step();
}

auto ASS_functional_test_lose::validate_enemy_reaction() -> void
{
    TArray<AActor*> enemies{};
	UGameplayStatics::GetAllActorsOfClass(this, ASS_Enemy_character::StaticClass(), enemies);

    for (auto& actor : enemies)
	{
        auto enemy = Cast<ASS_Enemy_character>(actor);
		AssertTrue(enemy->b_aiming_,              "Enemy is aiming.");
        AssertTrue(enemy->b_fire_button_pressed_, "Enemy is firing.");
	}

    progress_test_step();
}

auto ASS_functional_test_lose::verify_lose_game() -> void
{
    if (controller_ref_)
    {
        // Is End game widget visible?
        AssertTrue(controller_ref_->lose_screen_ref_->GetVisibility() == EVisibility::Visible, "Lose Game widget active.");
    }
    else
    {
        abort_test();
    }
    
    progress_test_step();
}
