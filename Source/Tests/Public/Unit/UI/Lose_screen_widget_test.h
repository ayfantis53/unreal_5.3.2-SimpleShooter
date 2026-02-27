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
#include "UI/SS_Widget_lose_screen.h"

/**
 *  Test class suite to assist Unit testing for Lose game widget text
 */
class Lose_screen_widget_test
{
public:
    /* --------------------- MEMBER VARS -------------------- */

    /// @brief Get lost game text.
    /// @return FString.
    static auto get_end_game_text(TSharedPtr<class SSS_Widget_lose_screen> widget_ref) -> FString
    {
        return widget_ref->lose_game_text_;
    }

    /// @brief Calls lose_game_widget set game over text function.
    /// @return FString.
    static auto get_resart_game_text(TSharedPtr<class SSS_Widget_lose_screen> widget_ref) -> FString
    {
        return widget_ref->level_restart_text_;
    }
};