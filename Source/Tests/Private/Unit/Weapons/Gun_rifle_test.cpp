// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //
#include "Unit/Weapons/Gun_rifle_test.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(spawn_gun_rifle_test, "UEUnitTests.Weapons.Rifle.SpawnActor", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto spawn_gun_rifle_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a basepawn.
    const auto world  = UWorld::CreateWorld(EWorldType::Game, false);
    auto weapon       = world->SpawnActor<ASS_Gun_rifle>();

    //// TEST ////
    
    // Test Rifle weapon was made.
    TestNotNull("Rifle Weapon Made",     weapon                                       );
    // Test all components were made.
    TestTrue("Is Automatic flag Set",    Gun_rifle_test::get_is_automatic(weapon)     );
    TestEqual("Damage amountcorrect",    Gun_rifle_test::get_gun_damage(weapon), 60.f );
    TestEqual("Auto rate correct",       Gun_rifle_test::get_auto_rate(weapon),  0.15f);
    TestEqual("Mesh location correct",   Gun_rifle_test::get_weapon_mesh(weapon)->GetRelativeLocation(), FVector(0.f, -14.5f, -2.2f));

    TestEqual("Fire montage anim set",   Gun_rifle_test::get_fire_anim(weapon),  "Fire Rifle");
    TestEqual("Gun Zoom FOV correct",    Gun_rifle_test::get_gun_zoom(weapon),   60.f );

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(setup_gun_rifle_test, "UEUnitTests.Weapons.Rifle.Setup", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto setup_gun_rifle_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a basepawn.
    const auto world  = UWorld::CreateWorld(EWorldType::Game, false);
    auto weapon       = world->SpawnActor<ASS_Gun_rifle>();

    //// TEST ////
    
    // Test Rifle weapon was made.
    TestNotNull("Rifle Weapon Made",     weapon                                   );
    // Test all components were made.
    TestNotNull("Weapon mesh Made",      Gun_rifle_test::get_weapon_mesh(weapon)  );
    TestNotNull("Projectile spawn Made", Gun_rifle_test::get_proj_spawn_pt(weapon));
    TestNotNull("Bullet trail set",      Gun_rifle_test::get_bullet_trail(weapon) );
    TestNotNull("Muzzle flash Made",     Gun_rifle_test::get_muzzle_flash(weapon) );
    TestNotNull("Muzzle Sound Set",      Gun_rifle_test::get_muzzle_sound(weapon) );
    TestNotNull("Impact sound set",      Gun_rifle_test::get_impact_sound(weapon) );

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}