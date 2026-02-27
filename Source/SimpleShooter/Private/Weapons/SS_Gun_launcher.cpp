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

#include "Weapons/SS_Gun_launcher.h"


ASS_Gun_launcher::ASS_Gun_launcher()
{
	// Setup rifle (self)
	b_is_projectile_class_ = true;
	camera_zoomed_fov_     = 60.f;
	max_range_             = 0.f;
	damage_                = 0.f;
	b_automatic_           = false;
	automatic_fire_rate_   = 1.f;
	weapon_fire_montage_   = "Fire Launcher";

	// Setup rifle mesh component.
	setup_paths();
	mesh_comp_->SetRelativeLocation(FVector(0.f, -15.24582f, -5.43638f));

	// Orient grenade projectiles correctly.
	projectile_spawn_point_->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
	projectile_spawn_point_->SetRelativeLocation(FVector(0.f, 65.f, 15.f));
}

auto ASS_Gun_launcher::setup_paths() -> void
{
	// Set path to our muzzle flash particle system.
	static ConstructorHelpers::FObjectFinder<UParticleSystem> muzzle_flash_container(*muzzle_flash_path_);
	if (muzzle_flash_container.Succeeded())
	{
		muzzle_flash_ = muzzle_flash_container.Object;
	}

	// Set path to our muzzle sound cue.
	static ConstructorHelpers::FObjectFinder<USoundBase> muzzle_sound_container(*muzzle_sound_path_);
	if (muzzle_sound_container.Succeeded())
	{
		muzzle_sound_ = muzzle_sound_container.Object;
	}

	// Set path to our skeletal mesh.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> rifle_mesh_container(*launcher_skeleton_path_);
	if (rifle_mesh_container.Succeeded())
	{
		mesh_comp_->SetSkeletalMesh(rifle_mesh_container.Object);
	}
}
