// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //#pragma once

// Unreal headers
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SS_Game_mode_kill_em_all.generated.h"


/**
 *	Game Mode handles what happens when all enemies die or player dies
 */
UCLASS()
class SIMPLESHOOTER_API ASS_Game_mode_kill_em_all : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	/// @brief Sets default values for this GameMode's properties.
	ASS_Game_mode_kill_em_all();

	/// @brief Function that sets if player won or not calls end game.
	/// @param pawn_ref reference to player.
	auto pawn_killed(APawn* pawn_ref) -> void;

private:
	/// @brief Handle win or lose condition for player.
	/// @param b_is_player_winner boolean that says if player won or not.
	auto end_game(bool b_is_player_winner) -> void;
};
