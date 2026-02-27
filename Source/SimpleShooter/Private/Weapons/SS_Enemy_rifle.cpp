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

#include "Weapons/SS_Enemy_rifle.h"


ASS_Enemy_rifle::ASS_Enemy_rifle()
{
	// Setup rifle (self).
	b_automatic_         = true;
	automatic_fire_rate_ = 0.17f;

	// Setup rifle mesh component.
	setup_paths();
	mesh_comp_->SetRelativeLocation(FVector(0.f, -14.5f, -2.2f));
}

auto ASS_Enemy_rifle::setup_paths() -> void
{
	// Set path to our muzzle flash particle system.
	static ConstructorHelpers::FObjectFinder<UParticleSystem> muzzle_flash_container(*muzzle_flash_path_);
	if (muzzle_flash_container.Succeeded())
	{
		muzzle_flash_ = muzzle_flash_container.Object;
	}

	// Set path to our bullet impact particle system.
	static ConstructorHelpers::FObjectFinder<UParticleSystem> bullet_impact_container(*bullet_impact_path_);
	if (bullet_impact_container.Succeeded())
	{
		bullet_impact_ = bullet_impact_container.Object;
	}

	// Set path to our bullet trail particle system.
	static ConstructorHelpers::FObjectFinder<UParticleSystem> bullet_trail_container(*bullet_trail_path_);
	if (bullet_trail_container.Succeeded())
	{
		bullet_trail_ = bullet_trail_container.Object;
	}

	// Set path to our muzzle sound cue.
	static ConstructorHelpers::FObjectFinder<USoundBase> muzzle_sound_container(*muzzle_sound_path_);
	if (muzzle_sound_container.Succeeded())
	{
		muzzle_sound_ = muzzle_sound_container.Object;
	}

	// Set path to our impact sound cue.
	static ConstructorHelpers::FObjectFinder<USoundBase> impact_sound_container(*impact_sound_path_);
	if (impact_sound_container.Succeeded())
	{
		impact_sound_ = impact_sound_container.Object;
	}
	// Set path to our skeletal mesh.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> rifle_mesh_container(*rifle_skeleton_path_);
	if (rifle_mesh_container.Succeeded())
	{
		mesh_comp_->SetSkeletalMesh(rifle_mesh_container.Object);
	}
}