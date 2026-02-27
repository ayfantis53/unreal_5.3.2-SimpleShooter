// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //
#include "Unit/Weapons/Gun_sniper_test.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(spawn_sniper_test, "UEUnitTests.Weapons.Sniper.SpawnActor", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto spawn_sniper_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a basepawn.
    const auto world  = UWorld::CreateWorld(EWorldType::Game, false);
    auto sniper = world->SpawnActor<ASS_Gun_sniper>();

    //// TEST ////
    
    // Test Sniper rifle was made.
    TestNotNull("Sniper Rifle Made",     sniper                                        );
    // Test all components were made.
    TestFalse("Is Automatic flag Set",   Gun_sniper_test::get_is_automatic(sniper)     );
    TestEqual("Gun Zoom FOV correct",    Gun_sniper_test::get_gun_zoom(sniper),   40.f );
    TestEqual("Damage amount correct",   Gun_sniper_test::get_gun_damage(sniper), 400.f);
    TestEqual("Auto rate correct",       Gun_sniper_test::get_auto_rate(sniper),  1.f  );
    TestEqual("Fire montage anim set",   Gun_sniper_test::get_fire_anim(sniper),  "Fire Heavy");

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(setup_sniper_test, "UEUnitTests.Weapons.Sniper.Setup", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto setup_sniper_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a basepawn.
    const auto world  = UWorld::CreateWorld(EWorldType::Game, false);
    auto sniper = world->SpawnActor<ASS_Gun_sniper>();

    //// TEST ////
    
    // Test Sniper rifle was made.
    TestNotNull("Sniper Rifle Made",     sniper                                    );
    // Test all components were made.
    TestNotNull("Weapon mesh Made",      Gun_sniper_test::get_weapon_mesh(sniper)  );
    TestNotNull("Projectile spawn Made", Gun_sniper_test::get_proj_spawn_pt(sniper));
    TestNotNull("Bullet trail set",      Gun_sniper_test::get_bullet_trail(sniper) );
    TestNotNull("Muzzle flash Made",     Gun_sniper_test::get_muzzle_flash(sniper) );
    TestNotNull("Muzzle Sound Set",      Gun_sniper_test::get_muzzle_sound(sniper) );
    TestNotNull("Impact sound set",      Gun_sniper_test::get_impact_sound(sniper) );

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}