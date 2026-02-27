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
#include "Unit/Characters/Enemy_character_test.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(spawn_enemy_test, "UEUnitTests.Characters.EnemyCharacter.SpawnActor", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto spawn_enemy_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a basepawn.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto enemy_char  = world->SpawnActor<ASS_Enemy_character>();

    //// TEST ////
    
    // Test Player Character was made.
    TestNotNull("Character Made", enemy_char);

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(enemy_begin_play_test, "UEUnitTests.Characters.EnemyCharacter.BeginPlay", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
    
auto enemy_begin_play_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a player character.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto enemy_char  = world->SpawnActor<ASS_Enemy_character>();

    //// TEST ////

    // Call BeginPlay.
    enemy_char->DispatchBeginPlay();

    TestNotNull("Enemy gun made", Enemy_character_test::get_enemy_gun(enemy_char)            );
    TestNotNull("Enemy gun set",  Enemy_character_test::get_enemy_gun(enemy_char)->GetOwner());
    TestEqual("Enemy got gun",    Cast<ASS_Enemy_character>(Enemy_character_test::get_enemy_gun(enemy_char)->GetOwner()), enemy_char);

    //// FINISH ////
    
    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(setup_enemy_character, "UEUnitTests.Characters.EnemyCharacter.SetupCharacter", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto setup_enemy_character::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a player character.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto enemy_char  = world->SpawnActor<ASS_Enemy_character>();

    // Setup Player Character.
    Enemy_character_test::call_setup_character(enemy_char);

    //// TEST ////

    // Test Character mesh setup properly.
    TestNotNull("Character mesh Made",   Enemy_character_test::get_char_mesh(enemy_char)      );
    TestEqual("Character mesh Location", Enemy_character_test::get_char_mesh(enemy_char)->GetRelativeLocation(), FVector(0.f, 0.f, -88.f) );
    TestEqual("Character mesh Rotation", Enemy_character_test::get_char_mesh(enemy_char)->GetRelativeRotation(), FRotator(0.f, -90.f, 0.f));
    // Animation montages setup correctly.
    TestNotNull("Hip fire montage made", Enemy_character_test::get_hip_fire_montage(enemy_char));

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}