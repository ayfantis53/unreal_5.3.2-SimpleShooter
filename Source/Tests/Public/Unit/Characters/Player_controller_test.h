// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //#include "Characters/SS_Player_controller.h"


/**
 *	Test class suite to assist Unit testing for Player Controller test to access private members of class
 */
class Player_controller_test
{
public:

    /* --------------------- MEMBER VARS -------------------- */

    /// @brief Get Win widget.
    /// @return TSharedPtr<SSS_Widget_win_screen>.
    static auto get_win_widget(ASS_Player_controller* controller) -> TSharedPtr<SSS_Widget_win_screen>
    {
        return controller->win_screen_ref_;
    }

    /// @brief Get Lose widget.
    /// @return TSharedPtr<SSS_Widget_win_screen>.
    static auto get_lose_widget(ASS_Player_controller* controller) -> TSharedPtr<SSS_Widget_lose_screen>
    {
        return controller->lose_screen_ref_;
    }

    /// @brief Get Win widget container.
    /// @return TSharedPtr<SWidget>.
    static auto get_win_swidget(ASS_Player_controller* controller) -> TSharedPtr<SWidget>
    {
        return controller->win_game_widget_container_;
    }

    /// @brief Get Lose widget container.
    /// @return TSharedPtr<SWidget>.
    static auto get_lose_swidget(ASS_Player_controller* controller) -> TSharedPtr<SWidget>
    {
        return controller->lose_game_widget_container_;
    }

    /* -------------------- FUNCTIONALITY ------------------- */

    /// @brief Call win widget setup.
    static auto call_set_up_win_widget(ASS_Player_controller* controller) -> void
    {
        return controller->set_up_win_widget();
    }

    /// @brief Call lose widget setup.
    static auto call_set_up_lose_widget(ASS_Player_controller* controller) -> void
    {
        return controller->set_up_lose_widget();
    }

    /// @brief Call GameHasEnded.
    static auto call_game_has_ended(ASS_Player_controller* controller, bool b_is_winner) -> void
    {
        return controller->GameHasEnded(nullptr, b_is_winner);
    }
};