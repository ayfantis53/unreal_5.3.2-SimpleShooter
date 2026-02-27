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
#include "UI/SS_Widget_win_screen.h"


/**
 *  Test class suite to assist Unit testing for Win game widget text
 */
class Win_screen_widget_test
{
public:
    /* --------------------- MEMBER VARS -------------------- */

    /// @brief Get lost game text.
    /// @return FString.
    static auto get_end_game_text(TSharedPtr<class SSS_Widget_win_screen> widget_ref) -> FString
    {
        return widget_ref->win_game_text_;
    }
};