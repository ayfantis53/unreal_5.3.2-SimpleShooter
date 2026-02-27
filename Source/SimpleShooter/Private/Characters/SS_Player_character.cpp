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

#include "Characters/SS_Player_character.h"
#include "Characters/SS_Player_controller.h"
#include "UI/SS_Widget_health_bar.h"
#include "UI/SS_Hud_shooter.h"

// Unreal headers.
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "SlateBasics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


ASS_Player_character::ASS_Player_character(const FObjectInitializer& ObjectInitializer)
{
	// get spring arm setup correctly.
	spring_arm_ = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	spring_arm_->SetupAttachment(RootComponent);
	spring_arm_->TargetArmLength          = 160.f;
	spring_arm_->bEnableCameraLag         = true;
	spring_arm_->bEnableCameraRotationLag = true;
	spring_arm_->CameraRotationLagSpeed   = 20.f;
	spring_arm_->bUsePawnControlRotation  = true;
	spring_arm_->SocketOffset             = FVector(0.f, 50.f, 70.f);

	// get camera setup correctly.
	camera_     = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera_->SetupAttachment(spring_arm_);

	// setup inputs and meshes.
	set_up_input();
	setup_character();
}

auto ASS_Player_character::BeginPlay() -> void
{
	Super::BeginPlay();

	// Get reference to player hud.
	hud_ref_               = Cast<ASS_Hud_shooter>(GetWorld()->GetFirstPlayerController()->GetHUD());

	// Add input mapping context.
	player_controller_ref_ = Cast<ASS_Player_controller>(GetController());
	if (player_controller_ref_)
	{
		// store the enhanced input subsystem for getting which key is triggered.
		if (const auto enhanced_input_subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(player_controller_ref_->GetLocalPlayer()))
		{
			enhanced_input_subsystem->AddMappingContext(shooting_mapping_context_, 0);
		}
	}

	// Set character camera field of view.
	if (camera_)
	{
		camera_default_fov_ = camera_->FieldOfView;
		camera_current_fov_ = camera_default_fov_;
	}

	// Give gun to character.
	gun_ref_ = GetWorld()->SpawnActor<ASS_Gun_base>(ASS_Gun_shotgun::StaticClass());
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	gun_ref_->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weapon_socket"));
	gun_ref_->SetOwner(this);
}

auto ASS_Player_character::Tick(float delta_time) -> void
{
	Super::Tick(delta_time);

	// Check to see if were Aiming.
	camera_interp_zoom(delta_time);

	// Should we recharge Health?
	if (health_ < max_health_ && b_recharge_ && !b_is_dead_)
	{
		health_ = FMath::FInterpConstantTo(health_, max_health_, delta_time, 50);
		health_bar_percent();
	}
	else
	{
		health_bar_percent();
	}
}

auto ASS_Player_character::health_bar_percent() const -> void
{
	if (hud_ref_->get_health_widget())
	{
		hud_ref_->get_health_widget()->progress_bar_ref->SetPercent(health_ / max_health_);
	}
}

auto ASS_Player_character::setup_character() -> void
{
	// Set Mesh to our skeletal mesh path.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletal_mesh_path_container(*skeletal_mesh_path_);
	if (skeletal_mesh_path_container.Succeeded())
	{
		character_mesh_ = GetMesh();
		character_mesh_->SetSkeletalMesh(skeletal_mesh_path_container.Object);
		character_mesh_->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
		character_mesh_->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	}

	static ConstructorHelpers::FObjectFinder<UClass> anim_class_container(*anim_bp_file_path_);
	if (anim_class_container.Succeeded() && character_mesh_)
	{
		character_mesh_->SetAnimInstanceClass(anim_class_container.Object);
	}

	// Set Hip Fire Montage for our skeletal mesh.
	static ConstructorHelpers::FObjectFinder<UAnimMontage> hip_fire_montage_container(*hip_fire_montage_path_);
	if (hip_fire_montage_container.Succeeded())
	{
		hip_fire_montage_ = hip_fire_montage_container.Object;
	}
}

// Called to bind functionality to input.
auto ASS_Player_character::SetupPlayerInputComponent(UInputComponent* player_input_component) -> void
{
	Super::SetupPlayerInputComponent(player_input_component);

	if (UEnhancedInputComponent* enhanced_input_component = CastChecked<UEnhancedInputComponent>(player_input_component))
	{
		// moving forward and backward.
		enhanced_input_component->BindAction(move_action_, ETriggerEvent::Triggered, this, &ASS_Player_character::move);

		// look up and down and turn.
		enhanced_input_component->BindAction(look_action_, ETriggerEvent::Triggered, this, &ASS_Player_character::look);

		// Character jumping.
		enhanced_input_component->BindAction(jump_action_, ETriggerEvent::Triggered, this, &ACharacter::Jump);

		// Character aiming weapon.
		enhanced_input_component->BindAction(aim_action_, ETriggerEvent::Triggered, this, &ASS_Player_character::aiming_button_pressed);
		enhanced_input_component->BindAction(aim_action_, ETriggerEvent::Completed, this, &ASS_Player_character::aiming_button_released);

		// Character firing weapon.
		enhanced_input_component->BindAction(shoot_action_, ETriggerEvent::Triggered, this, &ASS_Shooter_character::shoot);
		enhanced_input_component->BindAction(shoot_action_, ETriggerEvent::Completed, this, &ASS_Shooter_character::stop_shoot);
	}

}

auto ASS_Player_character::set_up_input() -> void
{
	// Set ShooterCharacter mapping context.
	static  ConstructorHelpers::FObjectFinder<UInputMappingContext> mapping_context_container(*imc_shooting_context_path_);
	if (mapping_context_container.Succeeded())
	{
		shooting_mapping_context_ = mapping_context_container.Object;
	}

	// Set aim input action.
	static  ConstructorHelpers::FObjectFinder<UInputAction> aim_action_container(*aim_action_path_);
	if (aim_action_container.Succeeded())
	{
		aim_action_ = aim_action_container.Object;
	}

	// Set jump input action.
	static  ConstructorHelpers::FObjectFinder<UInputAction> jump_action_container(*jump_action_path_);
	if (jump_action_container.Succeeded())
	{
		jump_action_ = jump_action_container.Object;
	}

	// Set look and turn input action.
	static  ConstructorHelpers::FObjectFinder<UInputAction> look_action_container(*look_action_path_);
	if (look_action_container.Succeeded())
	{
		look_action_ = look_action_container.Object;
	}

	// Set move input action.
	static  ConstructorHelpers::FObjectFinder<UInputAction> move_action_container(*move_action_path_);
	if (move_action_container.Succeeded())
	{
		move_action_ = move_action_container.Object;
	}

	// Set jump input action.
	static  ConstructorHelpers::FObjectFinder<UInputAction> shoot_action_container(*shoot_action_path_);
	if (shoot_action_container.Succeeded())
	{
		shoot_action_ = shoot_action_container.Object;
	}
}

auto ASS_Player_character::aiming_button_pressed(const FInputActionValue& value) -> void
{
	b_aiming_ = value.Get<bool>();
}

auto ASS_Player_character::aiming_button_released() -> void
{
	b_aiming_ = false;
}

auto ASS_Player_character::camera_interp_zoom(float delta_time) -> void
{
	// You are aiming so camera will zoom in or stopped aiming so camera will zoom out
	if (b_aiming_)
	{
		camera_current_fov_ = FMath::FInterpTo(camera_current_fov_, gun_ref_->get_camera_zoomed_fov(), delta_time, zoom_interp_speed_);
	}
	else
	{
		camera_current_fov_ = FMath::FInterpTo(camera_current_fov_, camera_default_fov_, delta_time, zoom_interp_speed_);
	}

	camera_->SetFieldOfView(camera_current_fov_);
}

auto ASS_Player_character::look(const FInputActionValue& value) -> void
{
	// Get players input from keys.
	const FVector2D look_axis_vector = value.Get<FVector2D>();

	// Adds a pitch input to the controller's control rotation
	// To look up and down.
	AddControllerPitchInput(look_axis_vector.Y);

	// Adds input to player's camera rotation, for turning left and right.
	AddControllerYawInput(look_axis_vector.X);

}

auto ASS_Player_character::move(const FInputActionValue& value) -> void
{
	// Get players input from keys.
	const FVector2D movement_vector = value.Get<FVector2D>();

	// Multiplies forward vector by axis value.
	const FVector forward = GetActorForwardVector();
	AddMovementInput(forward, movement_vector.Y);

	// Multiplies right vector by axis value.
	const FVector right = GetActorRightVector();
	AddMovementInput(right, movement_vector.X);

}