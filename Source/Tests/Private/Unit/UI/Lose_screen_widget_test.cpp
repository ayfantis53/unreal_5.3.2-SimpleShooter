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
#include "Unit/UI/Lose_screen_widget_test.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(lose_game_widget_spawn_test, "UEUnitTests.UI.LoseGameText.Spawn", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto lose_game_widget_spawn_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////
    
    // Get viewport and Initialize widget.
    TSharedPtr<class SSS_Widget_lose_screen> widget_ref = SNew(SSS_Widget_lose_screen);

    //// TEST ////

    // Test text correct for win.
    TestTrue("Lose game widget created", widget_ref.IsValid());

    //// FINISH ////

    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(lose_game_widget_text_test, "UEUnitTests.UI.LoseGameText.Text", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto lose_game_widget_text_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Initialize widget.
    TSharedPtr<class SSS_Widget_lose_screen> widget_ref = SNew(SSS_Widget_lose_screen);

    //// TEST ////

    // text to be tested.
    FString lose_text{ TEXT("You LOST!") };
    FString count_down_text{ TEXT("Level will restart in 5 seconds...") };

    // Test text correct for Loss.
    TestEqual("Losing text set correctly",  Lose_screen_widget_test::get_end_game_text(widget_ref),    lose_text      );
    TestEqual("Restart text set correctly", Lose_screen_widget_test::get_resart_game_text(widget_ref), count_down_text);

    //// FINISH ////

    // Finish test.
    return true;
}