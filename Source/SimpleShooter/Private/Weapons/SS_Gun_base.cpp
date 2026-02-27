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

#include "Weapons/SS_Gun_base.h"
#include "Weapons/SS_Projectile.h"
#include "FX/SS_Camera_shake_launcher.h"
#include "FX/SS_Camera_shake_weapon_fire.h"

// Unreal headers.
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


ASS_Gun_base::ASS_Gun_base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root_comp_ = CreateDefaultSubobject<USceneComponent>(TEXT("root_comp_"));
	SetRootComponent(root_comp_);

	// Mesh as root component.
	mesh_comp_ = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mesh_comp_"));
	mesh_comp_->SetupAttachment(root_comp_);

	// Projectile location so we know where to spawn grenades.
	projectile_spawn_point_ = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	projectile_spawn_point_->SetupAttachment(mesh_comp_);
}

auto ASS_Gun_base::BeginPlay() -> void
{
	Super::BeginPlay();
}

auto ASS_Gun_base::Tick(float delta_time) -> void
{
	Super::Tick(delta_time);
}

auto ASS_Gun_base::get_owner_controller() const -> AController*
{
	APawn* owner_pawn = Cast<APawn>(GetOwner());
	if (owner_pawn == nullptr)
	{
		return nullptr;
	}

	return owner_pawn->GetController();
}

auto ASS_Gun_base::gun_line_trace(FHitResult& hit, FVector shot_direction) -> bool
{
	// Make sure weapon has someone using it.
	AController* owner_controller = Cast<AController>(get_owner_controller());
	if (owner_controller == nullptr)
	{
		return false;
	}

	// Face where we will be shooting in correct direction.
	FVector  location{};
	FRotator rotation{};
	owner_controller->GetPlayerViewPoint(location, rotation);

	shot_direction = -rotation.Vector();
	FVector end    = location + rotation.Vector() * max_range_;

	// Make sure we dont hit ourselves in Line Trace for shoot.
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(GetOwner());

	// Send trace (bullet) out.
	return GetWorld()->LineTraceSingleByChannel(hit, location, end, ECollisionChannel::ECC_GameTraceChannel1, params);
}

auto ASS_Gun_base::play_fire_effects(FHitResult hit, FVector shot_direction) -> void
{
	// FX for muzzle.
	if (muzzle_sound_)
	{
		UGameplayStatics::SpawnSoundAttached(muzzle_sound_, mesh_comp_, TEXT("MuzzleFlashSocket"));
	}
	if (muzzle_flash_ && b_automatic_replay_)
	{
		muzzle_flash_comp_ = UGameplayStatics::SpawnEmitterAttached(muzzle_flash_, mesh_comp_, TEXT("MuzzleFlashSocket"));
		b_automatic_replay_ = false;
	}

	// FX for impact .
	if (bullet_impact_)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bullet_impact_, hit.Location, shot_direction.Rotation());
	}
	if (impact_sound_)
	{
		UGameplayStatics::SpawnSoundAttached(impact_sound_, mesh_comp_, TEXT("MuzzleFlashSocket"));
	}

	// FX for Bullet trail.
	if (bullet_trail_)
	{
		UParticleSystemComponent* beam = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), 
																				  bullet_trail_, 
																				  mesh_comp_->GetSocketLocation(TEXT("MuzzleFlashSocket")),
																				  mesh_comp_->GetSocketRotation(TEXT("MuzzleFlashSocket")));
		if (beam)
		{
			beam->SetVectorParameter(FName("Target"), hit.Location);
		}
	}

	// Camera Shake.
	if (APawn* gun_owner = Cast<APawn>(GetOwner()))
	{
		APlayerController* pc = Cast<APlayerController>(gun_owner->GetController());
		if (pc)
		{
			if (weapon_fire_montage_ == "Fire Heavy")
			{
				pc->ClientStartCameraShake(USS_Camera_shake_launcher::StaticClass());
			}
			else
			{
				pc->ClientStartCameraShake(USS_Camera_shake_weapon_fire::StaticClass());
			}
		}
	}
}

auto ASS_Gun_base::fire_weapon() -> void
{
	FHitResult hit;
	FVector    shot_direction;

	if (bool bSuccess = gun_line_trace(hit, shot_direction))
	{
		// FX for Impact of Bullet.
		play_fire_effects(hit, shot_direction);

		// damage_ what gets shot code.
		AActor* hit_actor = hit.GetActor();
		if (hit_actor)
		{
			FPointDamageEvent damage_event(damage_, hit, shot_direction, nullptr);
			AController*      owner_controller = get_owner_controller();
			hit_actor->TakeDamage(damage_, damage_event, owner_controller, this);
		}
	}
}

auto ASS_Gun_base::fire_projectile_weapon() -> void
{
	AActor* gun_owner = GetOwner();
	if (gun_owner && b_is_projectile_class_)
	{
		// Muzzle Sound Animation.
		if (muzzle_sound_)
		{
			UGameplayStatics::SpawnSoundAttached(muzzle_sound_, mesh_comp_, TEXT("MuzzleFlashSocket"));
		}
		// Muzzle Flash Animation.
		if (muzzle_flash_)
		{
			UGameplayStatics::SpawnEmitterAttached(muzzle_flash_, mesh_comp_, TEXT("MuzzleFlashSocket"));
		}

		// Camera Shake.
		APawn* gun_pawn_owner = Cast<APawn>(GetOwner());
		if (gun_pawn_owner)
		{
			APlayerController* pc = Cast<APlayerController>(gun_pawn_owner->GetController());
			if (pc)
			{
				pc->ClientStartCameraShake(USS_Camera_shake_launcher::StaticClass());
			}
		}

		// Spawn location.
		FVector  location 			   = projectile_spawn_point_->GetComponentLocation();
		FRotator rotation 			   = projectile_spawn_point_->GetComponentRotation();

		ASS_Projectile* projectile_ref = GetWorld()->SpawnActor<ASS_Projectile>(location, rotation);
		projectile_ref->SetOwner(this);
	}
}

auto ASS_Gun_base::pull_trigger() -> void
{
	// Normal gun with bullet (line trace attacks).
	if (!b_is_projectile_class_)
	{
		fire_weapon();
	}
	// Launcher weapon (grenades).
	else
	{
		fire_projectile_weapon();
	}

}

auto ASS_Gun_base::release_trigger() -> void
{
	// Deactivates automatic fire emitter since its infinite.
	if (muzzle_flash_comp_)
	{
		muzzle_flash_comp_->DeactivateSystem();
	}

	b_automatic_replay_ = true;
}

