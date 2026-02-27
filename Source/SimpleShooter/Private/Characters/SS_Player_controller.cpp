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

#include "Characters/SS_Player_controller.h"
#include "UI/SS_Widget_win_screen.h"
#include "UI/SS_Widget_lose_screen.h"

// Unreal headers.
#include "SlateBasics.h"
#include "Kismet/GameplayStatics.h"


auto ASS_Player_controller::BeginPlay() -> void
{
	Super::BeginPlay();
}

auto ASS_Player_controller::GameHasEnded(AActor* end_game_focus, bool b_is_winner) -> void
{
	Super::GameHasEnded(end_game_focus, b_is_winner);

	// What to do if we win or lose.
	if (b_is_winner)
	{
		set_up_win_widget();
	}
	else
	{
		// Make widget for lose screen condition.
		set_up_lose_widget();

		// Restart Game
		GetWorldTimerManager().SetTimer(restart_timer_, this, &APlayerController::RestartLevel, restart_delay_);
	}
}

auto ASS_Player_controller::set_up_win_widget() -> void
{
	// Draw Widget.
	if (GEngine && GEngine->GameViewport)
	{
		// Get viewport.
		UGameViewportClient* view_port = GEngine->GameViewport;

		// Initialize widget.
		win_screen_ref_ = SNew(SSS_Widget_win_screen);
		view_port->AddViewportWidgetContent(SAssignNew(win_game_widget_container_, SWeakWidget).PossiblyNullContent(win_screen_ref_));

		// Make widget seen on screen.
		win_screen_ref_->SetVisibility(EVisibility::Visible);
	}
}

auto ASS_Player_controller::set_up_lose_widget() -> void
{
	// Draw Widget.
	if (GEngine && GEngine->GameViewport)
	{
		// Get viewport.
		UGameViewportClient* view_port = GEngine->GameViewport;

		// Initialize widget.
		lose_screen_ref_ = SNew(SSS_Widget_lose_screen);
		view_port->AddViewportWidgetContent(SAssignNew(lose_game_widget_container_, SWeakWidget).PossiblyNullContent(lose_screen_ref_));

		// Make widget seen on screen.
		lose_screen_ref_->SetVisibility(EVisibility::Visible);
	}
}
