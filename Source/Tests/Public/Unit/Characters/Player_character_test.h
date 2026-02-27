// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //#include "Characters/SS_Player_character.h"

// Unreal headers
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"


/**
 *	Test class suite to assist Unit testing for Player Character test to access private members of class
 */
class Player_character_test
{
public:
    /* --------------------- COMPONENTS --------------------- */

    /// @brief Get Spring Arm component.
    /// @return USpringArmComponent*.
    static auto get_spring_arm_comp(ASS_Player_character* character) -> USpringArmComponent*
    {
        return character->spring_arm_;
    }

    /// @brief Get Camera component.
    /// @return UCameraComponent*.
    static auto get_camera_comp(ASS_Player_character* character) -> UCameraComponent*
    {
        return character->camera_;
    }

    /// @brief Get Skeletal character mesh component.
    /// @return USkeletalMeshComponent*.
    static auto get_char_mesh(ASS_Player_character* character) -> USkeletalMeshComponent*
    {
        return character->character_mesh_;
    }

    /* -------------------- INPUT ACTIONS ------------------- */

    /// @brief Get Input mapping context.
    /// @return UInputMappingContext*.
    static auto get_mapping_context(ASS_Player_character* character) -> UInputMappingContext*
    {
        return character->shooting_mapping_context_;
    }

    /// @brief Get Input mapping Context for aiming input.
    /// @return UInputAction*.
    static auto get_aiming_input(ASS_Player_character* character) -> UInputAction*
    {
        return character->aim_action_;
    }

    /// @brief Get Input mapping Context for jumping input.
    /// @return UInputAction*.
    static auto get_jumping_input(ASS_Player_character* character) -> UInputAction*
    {
        return character->jump_action_;
    }

    /// @brief Get Input mapping Context for looking input.
    /// @return UInputAction*.
    static auto get_looking_input(ASS_Player_character* character) -> UInputAction*
    {
        return character->look_action_;
    }

    /// @brief Get Input mapping Context for moving input.
    /// @return UInputAction*.
    static auto get_moving_input(ASS_Player_character* character) -> UInputAction*
    {
        return character->move_action_;
    }

    /// @brief Get Input mapping Context for shooting input.
    /// @return UInputAction*.
    static auto get_shooting_input(ASS_Player_character* character) -> UInputAction*
    {
        return character->shoot_action_;
    }

    /* --------------------- MEMBER VARS -------------------- */
    
    /// @brief Get player controller from player shooter.
    /// @return ASS_Player_controller*.
    static auto get_player_controller(ASS_Player_character* character) -> ASS_Player_controller*
    {
        return character->player_controller_ref_;
    }

    /// @brief Get Gun attached to player.
    /// @return ASS_Gun_base*.
    static auto get_player_gun(ASS_Player_character* character) -> ASS_Gun_base*
    {
        return character->gun_ref_;
    }

    /// @brief Get paiming bool to know if character is aiming or not.
    /// @return bool.
    static auto get_aiming(ASS_Player_character* character) -> bool
    {
        return character->b_aiming_;
    }

    /// @brief Get Gun fire anim montage.
    /// @return UAnimMontage*.
    static auto get_hip_fire_montage(ASS_Player_character* character) -> UAnimMontage*
    {
        return character->hip_fire_montage_;
    }

    /* -------------------- FUNCTIONALITY ------------------- */

    /// @brief Call character setup.
    static auto call_setup_character(ASS_Player_character* character) -> void
    {
        return character->setup_character();
    }

    //// AIMING ////

    /// @brief Call aiming button pressed.
    static auto call_aim_btn_pressed(ASS_Player_character* character, const FInputActionValue& value) -> void
    {
        return character->aiming_button_pressed(value);
    }

     /// @brief Call aiming button released.
    static auto call_aim_btn_released(ASS_Player_character* character) -> void
    {
        return character->aiming_button_released();
    }
};