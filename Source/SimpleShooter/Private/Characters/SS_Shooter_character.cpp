// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //
#include "Characters/SS_Shooter_character.h"
#include "Characters/SS_Player_controller.h"
#include "UI/SS_Widget_health_bar.h"
#include "AI/SS_Enemy_ai_controller.h"
#include "GameModes/SS_Game_mode_kill_em_all.h"
#include "Components/SS_Character_movement_component.h"

// Unreal headers.
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "BehaviorTree/BlackboardComponent.h"



ASS_Shooter_character::ASS_Shooter_character(const FObjectInitializer& ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCapsuleHalfHeight(88.f);
	GetCapsuleComponent()->SetCapsuleRadius(30.f);
}

auto ASS_Shooter_character::BeginPlay() -> void
{
	Super::BeginPlay();

	// give character health.
	health_ = max_health_;
}

auto ASS_Shooter_character::recharge_health() -> void
{
	b_recharge_ = true;
}

auto ASS_Shooter_character::TakeDamage(float damage_amount, FDamageEvent const& damage_event, AController* event_instigator, AActor* damage_causer) -> float
{
	float damage_to_apply = Super::TakeDamage(damage_amount, damage_event, event_instigator, damage_causer);

	// Handle character health reaching zero.
	if (health_ - damage_to_apply <= 0.f)
	{
		health_     = 0.f;
		b_is_dead_  = true;
		b_recharge_ = false;
		stop_shoot();
	}
	else
	{
		// Recharge health_ Timer Reset.
		b_recharge_       = false;
		GetWorldTimerManager().ClearTimer(timer_handle_shield_recharge_);
		GetWorldTimerManager().SetTimer(timer_handle_shield_recharge_, this, &ASS_Shooter_character::recharge_health, 3.f);

		// Apply Damage to Character.
		damage_to_apply   = FMath::Min(health_, damage_to_apply);
		health_ -= damage_to_apply;
	}

	// Handle character death.
	if (b_is_dead_) 
	{
		ASS_Game_mode_kill_em_all* game_mode = GetWorld()->GetAuthGameMode<ASS_Game_mode_kill_em_all>();
		if (game_mode != nullptr)
		{
			game_mode->pawn_killed(this);
		}

		b_recharge_       = false;
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// Handle enemy behavior when character dies.
		APawn* player_pawn = Cast <ASS_Shooter_character>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		if (GetOwner() == player_pawn)
		{
			// For all enemies: stop firing and being aggressive.
			for (ASS_Enemy_ai_controller* enemy_controller : TActorRange<ASS_Enemy_ai_controller>(GetWorld()))
			{
				if (enemy_controller)
				{
					enemy_controller->GetBlackboardComponent()->SetValueAsBool(FName(TEXT("character_dead")), true);

					Cast<ASS_Shooter_character>(enemy_controller->GetCharacter())->stop_shoot();
					Cast<ASS_Shooter_character>(enemy_controller->GetCharacter())->b_aiming_ = false;
				}
			}
		}
	}

	return damage_to_apply;
}

auto ASS_Shooter_character::shoot() -> void
{
	// Automatic fire rate functionality with timer.
	if (gun_ref_)
	{
		b_fire_button_pressed_ = true;
		start_fire_timer();
	}
}

auto ASS_Shooter_character::stop_shoot() -> void
{
	b_fire_button_pressed_ = false;
	gun_ref_->release_trigger();
}

auto ASS_Shooter_character::start_fire_timer() -> void
{
	if (gun_ref_ == nullptr)
	{
		return;
	}

	if (b_should_fire_)
	{
		gun_ref_->pull_trigger();
		b_should_fire_ = false;
		GetWorldTimerManager().SetTimer(auto_fire_timer_, this, &ASS_Shooter_character::auto_fire_reset, gun_ref_->get_automatic_fire_rate());

		// Play Recoil Animation.
		UAnimInstance* anim_instance = GetMesh()->GetAnimInstance();

		if (anim_instance && hip_fire_montage_)
		{
			anim_instance->Montage_Play(hip_fire_montage_);
			anim_instance->Montage_JumpToSection(*gun_ref_->get_weapon_fire_montage());
		}
	}
}

auto ASS_Shooter_character::auto_fire_reset() -> void
{
	if (gun_ref_ == nullptr)
	{
		return;
	}

	b_should_fire_ = true;

	if (b_fire_button_pressed_ && gun_ref_->get_b_automatic())
	{
		start_fire_timer();
	}
}