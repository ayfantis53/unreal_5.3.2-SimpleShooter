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
#include "Unit/Weapons/Enemy_rifle_test.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(spawn_enemy_rifle_test, "UEUnitTests.Weapons.EnemyRifle.SpawnActor", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto spawn_enemy_rifle_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a basepawn.
    const auto world  = UWorld::CreateWorld(EWorldType::Game, false);
    auto enemy_weapon = world->SpawnActor<ASS_Enemy_rifle>();

    //// TEST ////
    
    // Test Enemy weapon was made.
    TestNotNull("Enemy Weapon Made",     enemy_weapon                                         );
    // Test all components were made.
    TestTrue("Is Automatic flag Set",    Enemy_rifle_test::get_is_automatic(enemy_weapon)     );
    TestEqual("Damage amount correct",   Enemy_rifle_test::get_gun_damage(enemy_weapon), 40.f );
    TestEqual("Auto rate correct",       Enemy_rifle_test::get_auto_rate(enemy_weapon),  0.17f);
    TestEqual("Mesh location correct",   Enemy_rifle_test::get_weapon_mesh(enemy_weapon)->GetRelativeLocation(), FVector(0.f, -14.5f, -2.2f));

    TestEqual("Fire montage anim set",   Enemy_rifle_test::get_fire_anim(enemy_weapon),  "Fire Rifle");
    TestEqual("Gun Zoom FOV correct",    Enemy_rifle_test::get_gun_zoom(enemy_weapon),   60.f );

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(setup_enemy_rifle_test, "UEUnitTests.Weapons.EnemyRifle.Setup", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto setup_enemy_rifle_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a basepawn.
    const auto world  = UWorld::CreateWorld(EWorldType::Game, false);
    auto enemy_weapon = world->SpawnActor<ASS_Enemy_rifle>();

    //// TEST ////
    
    // Test Enemy weapon was made.
    TestNotNull("Enemy Weapon Made",     enemy_weapon                                     );
    // Test all components were made.
    TestNotNull("Weapon mesh Made",      Enemy_rifle_test::get_weapon_mesh(enemy_weapon)  );
    TestNotNull("Projectile spawn Made", Enemy_rifle_test::get_proj_spawn_pt(enemy_weapon));
    TestNotNull("Bullet trail set",      Enemy_rifle_test::get_bullet_trail(enemy_weapon) );
    TestNotNull("Muzzle flash Made",     Enemy_rifle_test::get_muzzle_flash(enemy_weapon) );
    TestNotNull("Muzzle Sound Set",      Enemy_rifle_test::get_muzzle_sound(enemy_weapon) );
    TestNotNull("Impact sound set",      Enemy_rifle_test::get_impact_sound(enemy_weapon) );

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}