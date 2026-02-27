// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //
#include "Unit/UI/Health_bar_widget_test.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(health_widget_spawn_test, "UEUnitTests.UI.HealthBar.Spawn", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto health_widget_spawn_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////
    
    // Get viewport and Initialize widget.
    TSharedPtr<class SSS_Widget_health_bar> widget_ref = SNew(SSS_Widget_health_bar);

    //// TEST ////

    // Test text correct for win.
    TestTrue("Health bar widget created", widget_ref.IsValid());

    //// FINISH ////

    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(health_bar_widget_text_test, "UEUnitTests.UI.HealthBar.Percentage", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto health_bar_widget_text_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Initialize widget.
    TSharedPtr<class SSS_Widget_health_bar> widget_ref = SNew(SSS_Widget_health_bar);

    //// TEST ////

    // Health bar starts at 100%.
    TestEqual("Health percent is 100",  Health_bar_widget_test::get_full_percent(widget_ref), 100.f);

    //// FINISH ////

    // Finish test.
    return true;
}