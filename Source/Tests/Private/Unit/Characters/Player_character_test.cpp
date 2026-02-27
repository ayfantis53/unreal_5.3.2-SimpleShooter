// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //
#include "Unit/Characters/Player_character_test.h"
#include "UI/SS_Hud_shooter.h"
#include "Characters/SS_Player_controller.h"

// Unreal headers.
#include "GameFramework/SpringArmComponent.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(spawn_character_test, "UEUnitTests.Characters.PlayerCharacter.SpawnActor", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto spawn_character_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a basepawn.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto player_char = world->SpawnActor<ASS_Player_character>();

    //// TEST ////
    
    // Test Player Character was made.
    TestNotNull("Character Made",       player_char                                                                         );
    // Test spring arm setup correctly.
    TestNotNull("Spring Arm Made",    Player_character_test::get_spring_arm_comp(player_char)                               );
    TestEqual("TargetArm length set", Player_character_test::get_spring_arm_comp(player_char)->TargetArmLength,        160.f);
    TestTrue("Enable Camera lag set", Player_character_test::get_spring_arm_comp(player_char)->bEnableCameraLag             );
    TestTrue("Cam rotation lag set",  Player_character_test::get_spring_arm_comp(player_char)->bEnableCameraRotationLag     );
    TestEqual("Camera lag speed set", Player_character_test::get_spring_arm_comp(player_char)->CameraRotationLagSpeed, 20.f );
    TestTrue("Use Control Rot set",   Player_character_test::get_spring_arm_comp(player_char)->bUsePawnControlRotation      );
    TestEqual("Socket Offset set",    Player_character_test::get_spring_arm_comp(player_char)->SocketOffset, FVector(0.f, 50.f, 70.f));
    // Test Camera setup correctly.
    TestNotNull("Camera Made ",       Player_character_test::get_camera_comp(player_char)                                   );

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(setup_player_input_test, "UEUnitTests.Characters.PlayerCharacter.SetupPlayerInput", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto setup_player_input_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a player character.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto player_char = world->SpawnActor<ASS_Player_character>();

    // Setup Player Input.
    auto       comp  = NewObject<UEnhancedInputComponent>();
    player_char->SetupPlayerInputComponent(comp);

    //// TEST ////

    // Test Bindings were added to the Player Input Component.
    TestTrue("Player Input Setup successfully", comp->HasBindings());

    // All Input actions were populated.
    TestNotNull("Mapping context Made", Player_character_test::get_mapping_context(player_char));
    TestNotNull("Aiming Input Made",    Player_character_test::get_aiming_input(player_char)   );
    TestNotNull("Jumping Input Made",   Player_character_test::get_jumping_input(player_char)  );
    TestNotNull("Looking Input Made",   Player_character_test::get_looking_input(player_char)  );
    TestNotNull("Moving Input Made",    Player_character_test::get_moving_input(player_char)   );
    TestNotNull("Shooting Input Made",  Player_character_test::get_shooting_input(player_char) );

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(setup_player_character, "UEUnitTests.Characters.PlayerCharacter.SetupCharacter", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto setup_player_character::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a player character.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto player_char = world->SpawnActor<ASS_Player_character>();

    // Setup Player Character.
    Player_character_test::call_setup_character(player_char);

    //// TEST ////

    // Test Character mesh setup properly.
    TestNotNull("Character mesh Made",   Player_character_test::get_char_mesh(player_char)       );
    TestEqual("Character mesh Location", Player_character_test::get_char_mesh(player_char)->GetRelativeLocation(), FVector(0.f, 0.f, -88.f) );
    TestEqual("Character mesh Rotation", Player_character_test::get_char_mesh(player_char)->GetRelativeRotation(), FRotator(0.f, -90.f, 0.f));
    TestNotNull("Anim instance made",    Player_character_test::get_char_mesh(player_char)->GetAnimInstance());
    // Animation montages setup correctly.
    TestNotNull("Hip fire montage made", Player_character_test::get_hip_fire_montage(player_char));

    //// FINISH ////

    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(char_begin_play_test, "UEUnitTests.Characters.PlayerCharacter.BeginPlay", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
    
auto char_begin_play_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a player character.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto player_char = world->SpawnActor<ASS_Player_character>();

    // Setup player controller (Spawn and posess character).
    auto controller  = world->SpawnActor<ASS_Player_controller>();
    world->AddController(controller);
    controller->Possess(player_char);

    //// TEST ////

    // Call BeginPlay.
    player_char->DispatchBeginPlay();

    // Test all components were made and projectile was bound to delegate.
    TestNotNull("Player controller for character Made", Player_character_test::get_player_controller(player_char));

    // Gun was made for player character.
    TestNotNull("Player gun made", Player_character_test::get_player_gun(player_char)            );
    TestNotNull("Player gun set",  Player_character_test::get_player_gun(player_char)->GetOwner());
    TestEqual("Player got gun",    Cast<ASS_Player_character>(Player_character_test::get_player_gun(player_char)->GetOwner()), player_char);
    
    //// FINISH ////
    
    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(character_aim_test, "UEUnitTests.Characters.PlayerCharacter.aiming", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
    
auto character_aim_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create game and create a player character.
    const auto world = UWorld::CreateWorld(EWorldType::Game, false);
    auto player_char = world->SpawnActor<ASS_Player_character>();

    //// TEST ////

    // Aiming button Pressed.
    Player_character_test::call_aim_btn_pressed(player_char, FInputActionValue(true));
    // Test all components were made and projectile was bound to delegate.
    TestTrue("Player controller for character Made", Player_character_test::get_aiming(player_char));

    // Aiming button Released.
    Player_character_test::call_aim_btn_released(player_char);
    // Test all components were made and projectile was bound to delegate.
    TestFalse("Player controller for character Made", Player_character_test::get_aiming(player_char));

    //// FINISH ////
    
    // Destroy Game.
    world->CleanupWorld();
    // Finish test.
    return true;
}

