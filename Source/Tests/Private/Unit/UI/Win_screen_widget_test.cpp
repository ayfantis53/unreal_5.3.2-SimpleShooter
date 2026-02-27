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
#include "Unit/UI/Win_screen_widget_test.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(win_game_widget_spawn_test, "UEUnitTests.UI.WinGameText.Spawn", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto win_game_widget_spawn_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////
    
    // Get viewport and Initialize widget.
    TSharedPtr<class SSS_Widget_win_screen> widget_ref = SNew(SSS_Widget_win_screen);

    //// TEST ////

    // Test text correct for win.
    TestTrue("Win game widget created", widget_ref.IsValid());

    //// FINISH ////

    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(win_game_widget_text_test, "UEUnitTests.UI.WinGameText.Text", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto win_game_widget_text_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Initialize widget.
    TSharedPtr<class SSS_Widget_win_screen> widget_ref = SNew(SSS_Widget_win_screen);

    //// TEST ////

    // text to be tested.
    FString win_text{ TEXT("You WIN!!!") };

    // Test text correct for Loss.
    TestEqual("Winning text set correctly",  Win_screen_widget_test::get_end_game_text(widget_ref), win_text);

    //// FINISH ////

    // Finish test.
    return true;
}