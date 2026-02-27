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
#include "Unit/Components/Movement_component_test.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(movement_spawn_test, "UEUnitTests.Components.MovementComponent.Spawn", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto movement_spawn_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a tank pawn.
    const auto world     = UWorld::CreateWorld(EWorldType::Game, false);
    auto       character = world->SpawnActor<ASS_Enemy_character>(FVector(0.f), FRotator(0.f));

    //// TEST ////

    // Test all movement component was created.
    TestNotNull("Movement Component created", Movement_component_test::get_movement_component(character));

    //// FINISH ////
    
    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(acceleration_paths_set_test, "UEUnitTests.Components.MovementComponent.AccelerationValueSet", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto acceleration_paths_set_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a tank pawn.
    const auto world     = UWorld::CreateWorld(EWorldType::Game, false);
    auto       character = world->SpawnActor<ASS_Enemy_character>(FVector(0.f), FRotator(0.f));

    //// TEST ////

    // Test acceleration path is on so enemies can move on nav mesh.
    TestTrue("Acceleration for paths set", Movement_component_test::acceleration_paths_value(character));

    //// FINISH ////
    
    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}