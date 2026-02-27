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
#pragma once

// Unreal headers
#include "CoreMinimal.h"
#include "Characters/SS_Shooter_character.h"
#include "SS_Player_character.generated.h"



class  UInputAction;
class  UInputComponent;
class  ASS_Hud_shooter;
struct FInputActionValue;
class  UInputMappingContext;
class  ASS_Player_controller;

/**
 * 	Playable character for User (Shooter)
 */
UCLASS()
class SIMPLESHOOTER_API ASS_Player_character : public ASS_Shooter_character
{
	GENERATED_BODY()
	
public:
	/// @brief Sets default values for this character's properties..
	/// @param ObjectInitializer controls how default values & settings are applied to new objects when creating subobjects.
	ASS_Player_character(const FObjectInitializer& ObjectInitializer);

	/// @brief Called every frame.
	/// @param delta_time Time taken between the frames of the gameplay can differ.
	auto Tick(float delta_time) -> void override;

	/// @brief Called to bind functionality to input.
	/// @param player_input_component Allows a Pawn to set up custom input bindings.
	auto SetupPlayerInputComponent(UInputComponent* player_input_component) -> void override;

	/// @brief Percent of full health for progress bar visual.
	auto health_bar_percent() const -> void;

protected:
	/// @brief Called when the game starts or when spawned.
	auto BeginPlay() -> void override;

	/// @brief setup of all constructor helpers to get paths of assets.
	virtual auto setup_character() -> void;

private:
	/// @brief Populates inputs filepaths for Constructor Helpers.
	auto set_up_input() -> void;

	/// @brief Player camera zooms in.
	/// @param value struct holding input action boolean values.
	auto aiming_button_pressed(const FInputActionValue& value) -> void;

	/// @brief Player camera reverts to original location.
	auto aiming_button_released() -> void;

	/// @brief Interpolates btween normal and zoomed camera view (for aiming).
	/// @param delta_time Time taken between the frames of the gameplay can differ.
	auto camera_interp_zoom(float delta_time) -> void;

	/// @brief lets character look up and turn sideways.
	/// @param value struct holding input action axis values.
	auto look(const FInputActionValue& value) -> void;

	/// @brief moves character left right forward backward.
	/// @param value struct holding input action axis values.
	auto move(const FInputActionValue& value) -> void;

	/* --------------------- REFERENCES --------------------- */

	/// @brief Reference to player controller.
	ASS_Hud_shooter* hud_ref_;

	/// @brief Reference to player controller.
	ASS_Player_controller* player_controller_ref_;

	/* --------------------- COMPONENTS --------------------- */

	//// POINTERS TO COMPONENTS ////

	/// @brief Maintains fixed distance from parent, retracts the children in collision, and spring back when not.
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* spring_arm_;

	/// @brief Represents a camera viewpoint and settings.
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* camera_;

	//// PATHS TO MESH COMPONENTS ////

	/// @brief path to players skeletal mesh in Content folder.
	FString skeletal_mesh_path_{ "SkeletalMesh'/Game/AssetPacks/ParagonWraith/Characters/Heroes/Wraith/Skins/ODGreen/Meshes/Wraith_ODGreen'" };

	/* -------------------- INPUT ACTIONS ------------------- */

	//// POINTERS TO INPUT ACTIONS ////

	/// @brief Mapping Context for input, passed to player subsystem.
	UPROPERTY(VisibleAnywhere)
	UInputMappingContext* shooting_mapping_context_;

	/// @brief Mapping Context for aiming input, passed to player subsystem.						 - bound to <Right-Mouse-btn>
	UPROPERTY(VisibleAnywhere)
	UInputAction* aim_action_;

	/// @brief Mapping Context for jumping input, passed to player subsystem.						 - bound to <Space-Bar>
	UPROPERTY(VisibleAnywhere)
	UInputAction* jump_action_;

	/// @brief Mapping Context for looking up down and turning input, passed to player subsystem.	 - bound to <Mouse-XY 2D axis>
	UPROPERTY(VisibleAnywhere)
	UInputAction* look_action_;

	/// @brief Mapping Context for forward move input, passed to player subsystem.					 - bound to <W> <S> <D> <A>
	UPROPERTY(VisibleAnywhere)
	UInputAction* move_action_;

	/// @brief Mapping Context for shooting input, passed to player subsystem.					     - bound to <Left-mouse-btn>
	UPROPERTY(VisibleAnywhere)
	UInputAction* shoot_action_;

	//// PATHS TO INPUT ACTIONS ////

	/// @brief Path to imc_ShootingContext in Content folder.
	FString imc_shooting_context_path_{ "InputMappingContext'/Game/EnhancedInputs/IMC_ShooterContext.IMC_ShooterContext'" };

	/// @brief Path to imc_ShootingContext in Content folder.
	FString aim_action_path_{ "InputAction'/Game/EnhancedInputs/InputActions/IA_Aiming.IA_Aiming'" };

	/// @brief Path to IA_Jump in Content folder.
	FString jump_action_path_{ "InputAction'/Game/EnhancedInputs/InputActions/IA_Jump.IA_Jump'" };

	/// @brief Path to IA_Look in Content folder.
	FString look_action_path_{ "InputAction'/Game/EnhancedInputs/InputActions/IA_Look.IA_Look'" };

	/// @brief Path to IA_Move in Content folder.
	FString move_action_path_{ "InputAction'/Game/EnhancedInputs/InputActions/IA_Move.IA_Move'" };

	/// @brief Path to imc_ShootingContext in Content folder.
	FString shoot_action_path_{ "InputAction'/Game/EnhancedInputs/InputActions/IA_Shoot.IA_Shoot'" };

	/* ----------------------- TESTING ---------------------- */

	/// @brief Test classes to unit test this Character.
	friend class Player_character_test;

	/// @brief Test classes to function test this Player Character.
	friend class ASS_functional_test_player;
};
