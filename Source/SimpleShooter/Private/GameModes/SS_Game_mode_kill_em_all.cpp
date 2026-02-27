// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //
#include "GameModes/SS_Game_mode_kill_em_all.h"

// Unreal headers.
#include "EngineUtils.h"
#include "AI/SS_Enemy_ai_controller.h"
#include "GameFramework/Controller.h"

#include "UI/SS_Hud_shooter.h"
#include "Characters/SS_Player_character.h"
#include "Characters/SS_Player_controller.h"


ASS_Game_mode_kill_em_all::ASS_Game_mode_kill_em_all()
{
	// The class of PlayerController to spawn for players logging in.
	PlayerControllerClass = ASS_Player_controller::StaticClass();

	// The default pawn class used by players.
	DefaultPawnClass = ASS_Player_character::StaticClass();

	// HUD Class this game uses.
	HUDClass = ASS_Hud_shooter::StaticClass();
}

auto ASS_Game_mode_kill_em_all::pawn_killed(APawn* pawn_ref) -> void
{
	// Player Died and did not win game.
	if (APlayerController* player_controller = Cast<APlayerController>(pawn_ref->GetController()))
	{
		end_game(false);
	}

	// Player killed all of the enemies and won the game.
	for (ASS_Enemy_ai_controller* controller : TActorRange<ASS_Enemy_ai_controller>(GetWorld()))
	{
		if (!controller->b_is_dead())
		{
			return;
		}
	}

	end_game(true);
}

auto ASS_Game_mode_kill_em_all::end_game(bool b_is_player_winner) -> void
{
	for (AController* controller : TActorRange<AController>(GetWorld()))
	{
		// Did Player win or Lose?
		bool b_is_winner = controller->IsPlayerController() == b_is_player_winner;
		controller->GameHasEnded(controller->GetPawn(), b_is_winner);
	}
}