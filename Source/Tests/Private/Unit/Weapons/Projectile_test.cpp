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
#include "Unit/Weapons/Projectile_test.h"

// Unreal headers.
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(spawn_projectile_test, "UEUnitTests.Weapons.Projectile.SpawnProjectile", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto spawn_projectile_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a basepawn.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto projectile  = world->SpawnActor<ASS_Projectile>(FVector(0.f), FRotator(0.f));

    //// TEST ////

    // Test Projectile was made.
    TestNotNull("Projectile was Created",     projectile                                              );

    // Properties set correctly.
    TestTrue("Is Explosive flag Set",         Projectile_test::get_is_explosive(projectile)           );
    TestEqual("Gun damage set correctly",     Projectile_test::get_proj_damage(projectile),     250.f );
    TestEqual("Gun max damage set correct",   Projectile_test::get_proj_max_damage(projectile), 500.f );
    
    TestEqual("Projectile Scale set Correct", Projectile_test::get_projectile_mesh(projectile)->GetRelativeScale3D(),    FVector(0.2f));
    TestEqual("Trail partices set Correctly", Projectile_test::get_trail_particles_fx(projectile)->GetRelativeScale3D(), FVector(5.f) );
    // Projectile movement component setup.
    TestEqual("Proj Move comp max speed set", Projectile_test::get_projectile_movement_component(projectile)->MaxSpeed,     2'000.f   );
    TestEqual("Proj Move comp max speed set", Projectile_test::get_projectile_movement_component(projectile)->InitialSpeed, 2'000.f   );

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(begin_play_test, "UEUnitTests.Weapons.Projectile.BeginPlay", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
    
auto begin_play_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a basepawn.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto projectile  = world->SpawnActor<ASS_Projectile>(FVector(0.f), FRotator(0.f));

    //// TEST ////

    // Call BeginPlay.
    projectile->DispatchBeginPlay();

    // Test all components were made and projectile was bound to delegate.
    TestTrue("Projectile bound to delegate", Projectile_test::get_projectile_mesh(projectile)->OnComponentHit.IsBound());

    //// FINISH ////
    
    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(setup_projectile_test, "UEUnitTests.Weapons.Projectile.Setup", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto setup_projectile_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a basepawn.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto projectile  = world->SpawnActor<ASS_Projectile>();

    //// TEST ////
    
    // Test Projectile was made.
    TestNotNull("Projectile was Created",             projectile                                                    );
    // Test all components and effects were made.
    TestNotNull("Projectile Mesh Made ",              Projectile_test::get_projectile_mesh(projectile)              );
    TestNotNull("Projectile Movement Component made", Projectile_test::get_projectile_movement_component(projectile));
    TestNotNull("Trailing particles Made",            Projectile_test::get_trail_particles_fx(projectile)           );
    TestNotNull("Hit Particle Effects Made",          Projectile_test::get_hit_particles_fx(projectile)             );
    TestNotNull("Hit Sound Made",                     Projectile_test::get_hit_sound_fx(projectile)                 );

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}