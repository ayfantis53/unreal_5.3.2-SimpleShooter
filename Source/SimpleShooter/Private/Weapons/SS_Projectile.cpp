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

#include "Weapons/SS_Projectile.h"
#include "FX/SS_Camera_shake_launcher.h"

// Unreal headers.
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


ASS_Projectile::ASS_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Projectile Mesh
	projectile_mesh_              = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	projectile_mesh_->SetRelativeScale3D(transform_scale_);
	projectile_mesh_->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	SetRootComponent(projectile_mesh_);


	SpawnCollisionHandlingMethod  = ESpawnActorCollisionHandlingMethod::Undefined;

	// Projectile Smoke Trail
	trail_particles_              = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	trail_particles_->SetRelativeScale3D(trail_particle_scale_);
	trail_particles_->SetupAttachment(projectile_mesh_);

	setup_paths();

	// Projectile Movement component. 
	proj_move_comp_               = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	proj_move_comp_->MaxSpeed     = 2'000.f;
	proj_move_comp_->InitialSpeed = 2'000.f;
}

auto ASS_Projectile::BeginPlay() -> void
{
	Super::BeginPlay();

	projectile_mesh_->OnComponentHit.AddDynamic(this, &ASS_Projectile::OnHit);
}

auto ASS_Projectile::Tick(float delta_time) -> void
{
	Super::Tick(delta_time);
}

auto ASS_Projectile::setup_paths() -> void
{
	// Set path to our hit particles explosion effect.
	static ConstructorHelpers::FObjectFinder<UParticleSystem> hit_particles_container(*hit_particles_path_);
	if (hit_particles_container.Succeeded())
	{
		hit_particles_ = hit_particles_container.Object;
	}

	// Set path to our hit sound explosion effect.
	static ConstructorHelpers::FObjectFinder<USoundBase> hit_sound_container(*sound_particles_path_);
	if (hit_sound_container.Succeeded())
	{
		hit_sound_ = hit_sound_container.Object;
	}

	// Set path to our hit sound explosion effect.
	static ConstructorHelpers::FObjectFinder<UParticleSystem> trail_particles_container(*trail_particles_path_);
	if (trail_particles_container.Succeeded())
	{
		trail_particles_->SetTemplate(trail_particles_container.Object);
	}

	// Set path to our projectile static mesh.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> projectile_mesh_container(*projectile_mesh_path_);
	if (projectile_mesh_container.Succeeded())
	{
		projectile_mesh_->SetStaticMesh(projectile_mesh_container.Object);
	}
}

auto ASS_Projectile::OnHit(UPrimitiveComponent* hit_comp, AActor* other_actor, UPrimitiveComponent* other_comp, FVector normal_impulse, const FHitResult& hit) -> void
{
	// Find out who is Firing me.
	AActor* proj_owner                 = GetOwner();
	if (proj_owner == nullptr)
	{
		Destroy();
		return;
	}

	AController* proj_owner_instigator = proj_owner->GetInstigatorController();
	UClass* damage_type_class          = UDamageType::StaticClass();

	if (other_actor && other_actor != this && other_actor != proj_owner)
	{
		// Is it an explosive?
		if (b_explosive_)
		{
			TArray<AActor*> ignore_actors;
			UGameplayStatics::ApplyRadialDamageWithFalloff(GetWorld(), max_damage_, damage_, GetActorLocation(), 300.f, 300.f, 1.0f, nullptr, ignore_actors, this, GetInstigatorController(), ECollisionChannel::ECC_Visibility);
		}
		// Is it a regular projectile.
		else
		{
			UGameplayStatics::ApplyDamage(other_actor, damage_, proj_owner_instigator, this, damage_type_class);
		}

		// Play Effects.
		if (hit_particles_)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, hit_particles_, GetActorLocation(), GetActorRotation());
		}
		if (hit_sound_)
		{
			UGameplayStatics::PlaySoundAtLocation(this, hit_sound_, GetActorLocation(), GetActorRotation());
		}

		// Camera Shake Anim.
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(USS_Camera_shake_launcher::StaticClass());
	}

	// Remove projectile from game.
	Destroy();
}

