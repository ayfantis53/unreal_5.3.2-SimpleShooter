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
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SS_Projectile.generated.h"


class USoundBase;
class UParticleSystem;
class UCameraShakeBase;
class UParticleSystemComponent;
class UProjectileMovementComponent;

/**
 *	Class for Grenade launcher grenade projectiles
 */
UCLASS()
class SIMPLESHOOTER_API ASS_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	/// @brief Sets default values for this actor's properties.
	ASS_Projectile();

	/// @brief Called every frame
	/// @param delta_time Time taken between the frames of the gameplay can differ.
	auto Tick(float delta_time) -> void override;

protected:
	/// @brief Called when the game starts or when spawned.
	auto BeginPlay() -> void override;

	/// @brief Use Constructor helpers to populate all properties.
	auto setup_paths() -> void;

	/// @brief An event that's triggered when a component (part of an actor) experiences a collision.
	/// @param hit_comp       The primitive component that was hit.
	/// @param other_actor    The actor that caused the hit.
	/// @param other_comp     The primitive component of the actor that caused the hit.
	/// @param normal_impulse A vector representing the impulse applied to the hit component.
	/// @param hit            Struct with info about collision, ie: point o/impact and normal vector o/impact.
	UFUNCTION()
	void OnHit(UPrimitiveComponent* hit_comp, 
			   AActor*              other_actor, 
			   UPrimitiveComponent* other_comp, 
			   FVector              normal_impulse, 
			   const FHitResult&    hit);

private:
	/* --------------------- COMPONENTS --------------------- */

	//// POINTERS TO COMPONENTS ////

	/// @brief Mesh has to be the root component or this projectile functionality doesnt work.
	UPROPERTY()
	USceneComponent* root_comp_;

	/// @brief Clear sphere where we are going to use to attach our trailing particles to.
	UPROPERTY()
	UStaticMeshComponent* projectile_mesh_;

	/// @brief Component specifically designed for simulating movement of grenade.
	UPROPERTY()
	UProjectileMovementComponent* proj_move_comp_;

	//// PATHS TO MESH COMPONENTS ////

	/// @brief path to our static mesh for Constructor helpers.
	FString projectile_mesh_path_{ "StaticMesh'/Game/Weapons/FX/Meshes/SM_GrenadeSphere.SM_GrenadeSphere'" };

	/* ---------------------- EFFECTS ----------------------- */

	//// POINTERS TO FX ////

	/// @brief Base class that represents hit sound to be played.
	UPROPERTY()
	USoundBase* hit_sound_;

	/// @brief Complete projectile impact particle effect with multiple ParticleEmitters.
	UPROPERTY()
	UParticleSystem* hit_particles_;

	/// @brief component that renders projectile trail particle effects.
	UPROPERTY()
	UParticleSystemComponent* trail_particles_;

	//// PATHS TO FX ////

	/// @brief Path to explosion sound cue.
	FString sound_particles_path_{ "SoundCue'/Game/Weapons/FX/Sounds/Launcher/A_Explosion_Cue.A_Explosion_Cue'" };

	/// @brief Path to launcher impact sound cue.
	FString hit_particles_path_{ "ParticleSystem'/Game/Weapons/FX/ParticleSystems/P_Launcher_IH.P_Launcher_IH'" };

	/// @brief Path to launcher projectile sound cue.
	FString trail_particles_path_{ "ParticleSystem'/Game/Weapons/FX/ParticleSystems/P_Launcher_proj.P_Launcher_proj'" };

	/* --------------------- PROPERTIES --------------------- */

	/// @brief Damage projectile explosion does by outer impulse.
	float damage_{ 250.f };

	/// @brief Damage projectile explosion does by inner impulse.
	float max_damage_{ 500.f };

	/// @brief Is the projectile an impulse damage type. Different than a point (bullet).
	bool b_explosive_{ true };

	//// SIZING ////
	
	/// @brief Relative scale projectile mesh will be scaled to.
	FVector transform_scale_{ FVector(0.2f) };

	/// @brief Relative scale projectile mesh will be scaled to.
	FVector trail_particle_scale_{ FVector(5.f) };	

	/* ----------------------- TESTING ---------------------- */
	
	/// @brief Test classes to unit test this Actor.
	friend class Projectile_test;
};
