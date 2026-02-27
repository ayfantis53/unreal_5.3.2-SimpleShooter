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
#include "Unit/Characters/Player_controller_test.h"

// Unreal headers
#include "Engine/GameViewportClient.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(spawn_controller_test, "UEUnitTests.Characters.PlayerController.SpawnActor", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto spawn_controller_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a Player Controller.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto controller  = world->SpawnActor<ASS_Player_controller>();

    //// TEST ////
    
    // Test Player Controller was made.
    TestNotNull("Controller Made", controller);

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(setup_win_test, "UEUnitTests.Characters.PlayerController.SetupWin", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto setup_win_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a Player Controller.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto controller  = world->SpawnActor<ASS_Player_controller>();

    // TODO: Need to find out how to get GEngine->GameViewport into our UWorld 

    //// TEST ////
    
    Player_controller_test::call_set_up_win_widget(controller);

    // Test Win widget was made.
    TestTrue("Win widget was Made",           Player_controller_test::get_win_widget(controller).IsValid() );
    TestTrue("Win widget container was Made", Player_controller_test::get_win_swidget(controller).IsValid());

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(setup_lose_test, "UEUnitTests.Characters.PlayerController.SetupLose", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto setup_lose_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a Player Controller.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto controller  = world->SpawnActor<ASS_Player_controller>();

    //// TEST ////
    
    Player_controller_test::call_set_up_lose_widget(controller);

    // Test Lose widget was made.
    TestTrue("Lose widget was Made",           Player_controller_test::get_lose_widget(controller).IsValid() );
    TestTrue("Lose widget container was Made", Player_controller_test::get_lose_swidget(controller).IsValid());

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(setup_game_end_test, "UEUnitTests.Characters.PlayerController.GameHasEnded", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto setup_game_end_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a Player Controller.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto controller  = world->SpawnActor<ASS_Player_controller>();

    //// TEST ////
    
    // Test Win conditions work.
    Player_controller_test::call_game_has_ended(controller, true);

    TestTrue("Win widget was Made",           Player_controller_test::get_win_widget(controller).IsValid() );
    TestTrue("Win widget container was Made", Player_controller_test::get_win_swidget(controller).IsValid());

    // Test Lose conditions work.
    Player_controller_test::call_game_has_ended(controller, false);

    TestTrue("Lose widget was Made",           Player_controller_test::get_lose_widget(controller).IsValid() );
    TestTrue("Lose widget container was Made", Player_controller_test::get_lose_swidget(controller).IsValid());

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}