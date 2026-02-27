// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //
#include "Unit/Weapons/Gun_launcher_test.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(spawn_launcher_test, "UEUnitTests.Weapons.Launcher.SpawnActor", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto spawn_launcher_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a basepawn.
    const auto world  = UWorld::CreateWorld(EWorldType::Game, false);
    auto weapon       = world->SpawnActor<ASS_Gun_launcher>();

    //// TEST ////
    
    // Test Launcher weapon was made.
    TestNotNull("Launcher Weapon Made",  weapon                                         );
    // Test all components were made.
    TestFalse("Is Automatic flag Set",   Gun_launcher_test::get_is_automatic(weapon)     );
    TestEqual("Damage amountcorrect",    Gun_launcher_test::get_gun_damage(weapon), 0.0f );
    TestEqual("Auto rate correct",       Gun_launcher_test::get_auto_rate(weapon),  1.f  );
    TestEqual("Mesh location correct",   Gun_launcher_test::get_weapon_mesh(weapon)->GetRelativeLocation(), FVector(0.f, -15.24582f, -5.43638f));

    TestEqual("Fire montage anim set",   Gun_launcher_test::get_fire_anim(weapon),  "Fire Launcher");
    TestEqual("Gun Zoom FOV correct",    Gun_launcher_test::get_gun_zoom(weapon),   60.f );
    // Projectile mesh setup correctly.
    TestEqual("Projectile spawn Made",   Gun_launcher_test::get_proj_spawn_pt(weapon)->GetRelativeLocation(), FVector(0.f, 65.f, 15.f));
    TestEqual("Projectile spawn Made",   Gun_launcher_test::get_proj_spawn_pt(weapon)->GetRelativeRotation(), FRotator(0.f, 90.f, 0.f));

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(setup_launcher_test, "UEUnitTests.Weapons.Launcher.Setup", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto setup_launcher_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a basepawn.
    const auto world  = UWorld::CreateWorld(EWorldType::Game, false);
    auto weapon       = world->SpawnActor<ASS_Gun_launcher>();

    //// TEST ////
    
    // Test Launcher weapon was made.
    TestNotNull("Launcher Weapon Made",     weapon                                   );
    // Test all components were made.
    TestNotNull("Weapon mesh Made",      Gun_launcher_test::get_weapon_mesh(weapon)  );
    TestNotNull("Projectile spawn Made", Gun_launcher_test::get_proj_spawn_pt(weapon));
    TestNotNull("Muzzle flash Made",     Gun_launcher_test::get_muzzle_flash(weapon) );
    TestNotNull("Muzzle Sound Set",      Gun_launcher_test::get_muzzle_sound(weapon) );

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}