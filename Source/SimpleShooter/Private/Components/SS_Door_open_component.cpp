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

#include "Components/SS_Door_open_component.h"

// Unreal headers.
#include "Engine/World.h"
#include "Sound/SoundCue.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"


USS_Door_open_component::USS_Door_open_component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

auto USS_Door_open_component::BeginPlay() -> void
{
	Super::BeginPlay();

	// initialize door positions.
	initial_z_		  = GetOwner()->GetActorLocation().Z;
	current_z_		  = initial_z_;
	target_z_         = initial_z_ + 370.f;
	// initialize player character pawn.
	actor_opens_door_ = GetWorld()->GetFirstPlayerController()->GetPawn();
}

auto USS_Door_open_component::TickComponent(float delta_time, ELevelTick tick_type, FActorComponentTickFunction* this_tick_function) -> void
{
	Super::TickComponent(delta_time, tick_type, this_tick_function);

	// Chack every frame if door should be opening or closing.
	activate_trigger_volume(delta_time);
}

auto USS_Door_open_component::open_door(float delta_time) -> void
{
	// Open door at a constant speed.
	current_z_		  = FMath::FInterpConstantTo(current_z_, target_z_, delta_time, 150);
	FVector open_door = GetOwner()->GetActorLocation();
	open_door.Z		  = current_z_;
	
	GetOwner()->SetActorLocation(open_door);

	// make sure door doesnt loop sounds over eachother if character triggers pressure plate alot.
	if (door_opening_sound_ && !b_door_sound_)
	{
		// Set noise effects.
		b_door_sound_ = true;
		UGameplayStatics::PlaySound2D(this, door_opening_sound_);
	}
}

auto USS_Door_open_component::close_door(float delta_time) -> void
{
	// Set current vector back to initial vector and interp it to that location so door has to travel there.
	current_z_		   = FMath::FInterpConstantTo(current_z_, initial_z_, delta_time, 150);
	FVector close_door = GetOwner()->GetActorLocation();
	close_door.Z	   = current_z_;

	GetOwner()->SetActorLocation(close_door);

	// Set noise effects.
	b_door_sound_ = false;
}

auto USS_Door_open_component::activate_trigger_volume(float delta_time) -> void
{
	if (actor_opens_door_ == nullptr)
	{
		return;
	}

	// Character stepping on trigger, open door. 
	if (pressure_plate_ && pressure_plate_->IsOverlappingActor(actor_opens_door_))
	{
		open_door(delta_time);
	}
	// No character stepping on trigger, close door.
	else
	{	
		// if door is already closed do nothing 
		if (current_z_ == initial_z_)
		{
			return;
		}

		close_door(delta_time);
	}
}

