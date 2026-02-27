// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //
#include "Unit/Weapons/Gun_shotgun_test.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(spawn_shotgun_test, "UEUnitTests.Weapons.Shotgun.SpawnActor", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto spawn_shotgun_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a basepawn.
    const auto world  = UWorld::CreateWorld(EWorldType::Game, false);
    auto shotgun      = world->SpawnActor<ASS_Gun_shotgun>();

    //// TEST ////
    
    // Test Shotgun rifle was made.
    TestNotNull("Shotgun Rifle Made",    shotgun                                         );
    // Test all components were made.
    TestFalse("Is Automatic flag Set",   Gun_shotgun_test::get_is_automatic(shotgun)     );
    TestEqual("Gun Zoom FOV correct",    Gun_shotgun_test::get_gun_zoom(shotgun),   70.f );
    TestEqual("Damage amount correct",   Gun_shotgun_test::get_gun_damage(shotgun), 200.f);
    TestEqual("Auto rate correct",       Gun_shotgun_test::get_auto_rate(shotgun),  0.5f );
    TestEqual("Fire montage anim set",   Gun_shotgun_test::get_fire_anim(shotgun),  "Fire Launcher");

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(setup_shotgun_test, "UEUnitTests.Weapons.Shotgun.Setup", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto setup_shotgun_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a basepawn.
    const auto world  = UWorld::CreateWorld(EWorldType::Game, false);
    auto shotgun      = world->SpawnActor<ASS_Gun_shotgun>();

    //// TEST ////
    
    // Test Shotgun rifle was made.
    TestNotNull("Shotgun Rifle Made",     shotgun                                    );
    // Test all components were made.
    TestNotNull("Weapon mesh Made",      Gun_shotgun_test::get_weapon_mesh(shotgun)  );
    TestNotNull("Projectile spawn Made", Gun_shotgun_test::get_proj_spawn_pt(shotgun));
    TestNotNull("Muzzle flash Made",     Gun_shotgun_test::get_muzzle_flash(shotgun) );
    TestNotNull("Muzzle Sound Set",      Gun_shotgun_test::get_muzzle_sound(shotgun) );
    TestNotNull("Impact sound set",      Gun_shotgun_test::get_impact_sound(shotgun) );

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}