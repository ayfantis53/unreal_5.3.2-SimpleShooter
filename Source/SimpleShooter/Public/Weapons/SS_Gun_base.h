// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //#pragma once

// Unreal headers
#include "Particles/ParticleSystem.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SS_Gun_base.generated.h"


class ASS_Projectile;

/**
 *	Base class for all gun weapons in game
 */
UCLASS()
class SIMPLESHOOTER_API ASS_Gun_base : public AActor
{
	GENERATED_BODY()
	
public:	
	/// @brief Sets default values for this actor's properties.
	ASS_Gun_base();

	/// @brief Called every frame.
	/// @param delta_time time taken between the frames of the gameplay can differ.
	auto Tick(float delta_time) -> void override;

	/// @brief fires weapon with line trace or projectile depending on weapon type.
	auto pull_trigger() -> void;

	/// @brief resets automatic fire and any lingering emitter from muzzle fire.
	auto release_trigger() -> void;

	/// @brief All Getters for Shooter Character class to use. 
	FORCEINLINE auto get_b_automatic()         const -> bool    { return b_automatic_;         }
	FORCEINLINE auto get_camera_zoomed_fov()   const -> float   { return camera_zoomed_fov_;   }
	FORCEINLINE auto get_automatic_fire_rate() const -> float   { return automatic_fire_rate_; }
	FORCEINLINE auto get_weapon_fire_montage() const -> FString { return weapon_fire_montage_; }

protected:
	/// @brief Called when the game starts or when spawned.
	auto BeginPlay() -> void override;

	/// @brief Use Constructor helpers to populate all properties.
	virtual auto setup_paths() -> void PURE_VIRTUAL();

	/* --------------------- COMPONENTS --------------------- */

	//// POINTERS TO COMPONENTS ////

	/// @brief Base class for all Components.
	UPROPERTY()
	USceneComponent* root_comp_;

	/// @brief Renders a a 3D model with a skeleton and animation capabilities for guns.
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* mesh_comp_;

	/// @brief where the line trace or projectiles will spawn for firing effects.
	UPROPERTY(VisibleAnywhere)
	USceneComponent* projectile_spawn_point_;

	/// @brief Complete particle effect, with multiple emitters, allowing for muzzle flash effects.
	UPROPERTY(VisibleAnywhere)
	UParticleSystem* muzzle_flash_;

	/// @brief Container for muzzle flash effect, allowing control (infinite emitter) and visual effects.
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* muzzle_flash_comp_;

	/// @brief Complete particle effect, with multiple emitters, allowing for bullet impact effects.
	UPROPERTY(VisibleAnywhere)
	UParticleSystem* bullet_impact_;

	/* ---------------------- EFFECTS ----------------------- */

	//// SOUND ////

	/// @brief Base class that represents gunfire sound, that can be played within the engine.
	UPROPERTY()
	USoundBase* muzzle_sound_;

	/// @brief Base class that represents bullet impact sound, that can be played within the engine.
	UPROPERTY()
	USoundBase* impact_sound_;

	//// PARTICLE EFFECTS ////

	/// @brief Complete particle effect, with multiple emitters, allowing for bullet trail effects.
	UPROPERTY()
	UParticleSystem* bullet_trail_;

	//// ANIMATIONS ////

	/// @brief Name of the firing montage to play based on weapon.
	FString weapon_fire_montage_{ "Fire Rifle" };

	/* --------------------- PROPERTIES --------------------- */

	/// @brief default damage of weapon.
	float damage_{ 40.f };

	/// @brief default range for bullet or projectile.
	float max_range_{ 5000.f };

	/// @brief default zoom of weapon.
	float camera_zoomed_fov_{ 60.f };

	/// @brief boolean to tell us if this class is a launcher or gun class.
	bool b_is_projectile_class_{};

	//// AUTOMATIC OR SEMI FIRE ////

	/// @brief will this gun fire automatically or semi-automatic.
	bool b_automatic_{};

	/// @brief boolean to allow us to fire weapon (ensure we have delay between gun shots).
	bool b_automatic_replay_{ true };

	/// @brief how fast our gun will shoot, the smaller the numer the faster the fire rate.
	float automatic_fire_rate_{ 0.1f };

private:
	/// @brief Find out which character is using the gun.
	/// @return AController* of character using the weapon.
	auto get_owner_controller() const -> AController*;

	/// @brief Line trace by single to let game know whether to play FX of gunfire impact.
	/// @param hit            Location of bullet impact for our line trace.
	/// @param shot_direction Direction of shooting for our bullet line trace.
	/// @return bool if we hit anything or not.
	auto gun_line_trace(FHitResult& hit, FVector shot_direction) -> bool;

	/// @brief Animate the weapon's particle and sound FX.
	/// @param hit            Location of bullet impact for our impact FX.
	/// @param shot_direction Direction of shooting for our bullet impact FX.
	auto play_fire_effects(FHitResult hit, FVector shot_direction) -> void;

	/// @brief Character shoots a gun that does a bullet line trac.
	auto fire_weapon() -> void;

	/// @brief Character shoots a gun that spawn a grenade.
	auto fire_projectile_weapon() -> void;

	/* ----------------------- TESTING ---------------------- */
	
	/// @brief Test classes to unit test this Actor.
	friend class Enemy_rifle_test;
	friend class Gun_launcher_test;
	friend class Gun_rifle_test;
	friend class Gun_shotgun_test;
	friend class Gun_sniper_test;
};
