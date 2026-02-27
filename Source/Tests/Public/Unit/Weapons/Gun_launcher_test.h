// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //#include "Weapons/SS_Gun_launcher.h"


/**
 *	Test class suite to assist Unit testing for Launcher weapon test to access private members of class
 */
class Gun_launcher_test
{
public:
    /* --------------------- COMPONENTS --------------------- */

    /// @brief Get Weapon skeletal mesh component.
    /// @return USkeletalMeshComponent*.
    static auto get_weapon_mesh(ASS_Gun_launcher* weapon) -> USkeletalMeshComponent*
    {
        return weapon->mesh_comp_;
    }

    /* --------------------- MEMBER VARS -------------------- */

    //// GUN BASE ////

    /// @brief Get projectile spawn point.
    /// @return USceneComponent*.
    static auto get_proj_spawn_pt(ASS_Gun_launcher* weapon) -> USceneComponent*
    {
        return weapon->projectile_spawn_point_;
    }

    /// @brief Get Muzzle flash particle system.
    /// @return UParticleSystem*.
    static auto get_muzzle_flash(ASS_Gun_launcher* weapon) -> UParticleSystem*
    {
        return weapon->muzzle_flash_;
    }

    /// @brief Get muzzle sound.
    /// @return USoundBase*.
    static auto get_muzzle_sound(ASS_Gun_launcher* weapon) -> USoundBase*
    {
        return weapon->muzzle_sound_;
    }

    //// LAUNCHER ////

    /// @brief Get is automatic flag.
    /// @return bool.
    static auto get_is_automatic(ASS_Gun_launcher* weapon) -> bool
    {
        return weapon->b_automatic_;
    }

    /// @brief Get is automatic flag.
    /// @return float.
    static auto get_auto_rate(ASS_Gun_launcher* weapon) -> float
    {
        return weapon->automatic_fire_rate_;
    }

    /// @brief Get damage amount.
    /// @return float.
    static auto get_gun_damage(ASS_Gun_launcher* weapon) -> float
    {
        return weapon->damage_;
    }

    /// @brief Get damage amount.
    /// @return float.
    static auto get_gun_zoom(ASS_Gun_launcher* weapon) -> float
    {
        return weapon->camera_zoomed_fov_;
    }

    /// @brief Get damage amount.
    /// @return FString.
    static auto get_fire_anim(ASS_Gun_launcher* weapon) -> FString
    {
        return weapon->weapon_fire_montage_;
    }

    /* -------------------- FUNCTIONALITY ------------------- */

    /// @brief Call aiming button pressed.
    static auto call_setup_paths(ASS_Gun_launcher* weapon) -> void
    {
        return weapon->setup_paths();
    }
};