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
#include "Components/SS_Character_movement_component.h"
#include "Characters/SS_Enemy_character.h"


/**
 *	Test class suite to assist Unit testing for Movement Component test to access private members of class
 */
class Movement_component_test
{
public:
    /* --------------------- COMPONENTS --------------------- */

    /// @brief Get Movement component.
    /// @return USS_Character_movement_component*.
    static auto get_movement_component(ASS_Enemy_character* character) -> USS_Character_movement_component*
    {
        return Cast<USS_Character_movement_component>(character->GetCharacterMovement());
    }

    /* --------------------- MEMBER VARS -------------------- */

    /// @brief Get value of acceleration paths.
    /// @return bool if acceleration paths set.
    static auto acceleration_paths_value(ASS_Enemy_character* character) -> bool
    {
        return get_movement_component(character)->get_acceleration_path();
    }
};