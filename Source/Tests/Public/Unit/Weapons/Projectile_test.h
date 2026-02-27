// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //#include "Weapons/SS_Projectile.h"


/**
 *	Test class suite to assist Unit testing for Projectile test to access private members of class
 */
class Projectile_test
{
public:
    /* --------------------- COMPONENTS --------------------- */

    /// @brief Get the projectile mesh component.
    /// @return UStaticMeshComponent*.
    static auto get_projectile_mesh(ASS_Projectile* projectile) -> UStaticMeshComponent*
    {
        return projectile->projectile_mesh_;
    }

    /// @brief Get the projectile's movement component.
    /// @return UProjectileMovementComponent*.
    static auto get_projectile_movement_component(ASS_Projectile* projectile) -> UProjectileMovementComponent*
    {
        return projectile->proj_move_comp_;
    }

    /* --------------------- MEMBER VARS -------------------- */

    /// @brief Get damage amount.
    /// @return float.
    static auto get_proj_damage(ASS_Projectile* projectile) -> float
    {
        return projectile->damage_;
    }

    /// @brief Get max damage amount.
    /// @return float.
    static auto get_proj_max_damage(ASS_Projectile* projectile) -> float
    {
        return projectile->max_damage_;
    }

    /// @brief Get is explosive flag.
    /// @return bool.
    static auto get_is_explosive(ASS_Projectile* projectile) -> bool
    {
        return projectile->b_explosive_;
    }

    /* ----------------------- EFFECTS ---------------------- */

    /// @brief Get the projectile's trail particle's component.
    /// @return UParticleSystemComponent*.
    static auto get_trail_particles_fx(ASS_Projectile* projectile) -> UParticleSystemComponent*
    {
        return projectile->trail_particles_;
    }

    /// @brief Get the projectile's hit particles.
    /// @return UParticleSystem*.
    static auto get_hit_particles_fx(ASS_Projectile* projectile) -> UParticleSystem*
    {
        return projectile->hit_particles_;
    }

    /// @brief Get the projectile's USoundBase for making impact sound.
    /// @return USoundBase*.
    static auto get_hit_sound_fx(ASS_Projectile* projectile) -> USoundBase*
    {
        return projectile->hit_sound_;
    }
};