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
#include "Characters/SS_Enemy_character.h"


/**
 *	Test class suite to assist Unit testing for Enemy Character test to access private members of class
 */
class Enemy_character_test
{
public:
    /* --------------------- COMPONENTS --------------------- */

    /// @brief Get Character skeletal mesh component.
    /// @return USkeletalMeshComponent*.
    static auto get_char_mesh(ASS_Enemy_character* character) -> USkeletalMeshComponent*
    {
        return character->character_mesh_;
    }

    /* --------------------- MEMBER VARS -------------------- */

    /// @brief Get Gun fire anim montage.
    /// @return UAnimMontage*.
    static auto get_hip_fire_montage(ASS_Enemy_character* character) -> UAnimMontage*
    {
        return character->hip_fire_montage_;
    }

    /// @brief Get Gun attached to enemy.
    /// @return ASS_Gun_base*.
    static auto get_enemy_gun(ASS_Enemy_character* character) -> ASS_Gun_base*
    {
        return character->gun_ref_;
    }

    /* -------------------- FUNCTIONALITY ------------------- */

    /// @brief Call aiming button pressed.
    static auto call_setup_character(ASS_Enemy_character* character) -> void
    {
        return character->setup_character();
    }
};