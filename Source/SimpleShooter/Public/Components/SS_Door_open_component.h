// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //// Change Mobility of component to movable in Transform Properties
#pragma once

// Unreal headers
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SS_Door_open_component.generated.h"


class ATriggerVolume;

/**
 *	An actor component that gives our doors funtionality to move when activated by trigger volumes
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLESHOOTER_API USS_Door_open_component : public UActorComponent
{
	GENERATED_BODY()

public:	
	/// @brief Sets default values for this component's properties.
	USS_Door_open_component();

	/// @brief Called every frame
	/// @param delta_time         For time-based calculations and consistent behavior regardless of frame rate.
	/// @param tick_type          An enum of type ELevelTick that specifies the type of tick being executed. (LEVELTICK_Normal, LEVELTICK_TimeOnly, or LEVELTICK_PauseTick).
	/// @param this_tick_function A pointer to struct that provides access to properties and functions related to the tick execution, such as enabling or disabling ticking.
	auto TickComponent(float delta_time, ELevelTick tick_type, FActorComponentTickFunction* this_tick_function) -> void override;

protected:
	/// @brief Called when the game starts.
	auto BeginPlay() -> void override;

	/// @brief Moves door upward until reaching final position.
	/// @param delta_time Time taken between the frames of the gameplay can differ.
	auto open_door(float delta_time) -> void;

	/// @brief Moves door downward until reaching final position. 
	/// @param delta_time Time taken between the frames of the gameplay can differ.
	auto close_door(float delta_time) -> void;

	/// @brief If character is overlapping pressure plate, move door up.
	/// @param delta_time Time taken between the frames of the gameplay can differ.
	auto activate_trigger_volume(float delta_time) -> void;

private:
	/* -------------------- DOOR MOVEMENT ------------------ */

	//// POSITION ////

	/// @brief Get Initial position of the door.
	float initial_z_;

	/// @brief Position door is at in this exact moment.
	float current_z_;

	/// @brief Where I want the door to be after opening.
	float target_z_;

	//// TRIGGERS FOR MOVEMENT ////

	/// @brief Only player can open doors not AI.
	AActor* actor_opens_door_;

	/// @brief Special type of actor that serves as trigger mechanism for character overlapping it.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	ATriggerVolume* pressure_plate_;

	//// EFFECTS ////

	/// @brief make sure door doesnt loop sounds over eachother if character triggers pressure plate alot.
	bool b_door_sound_;

	/// @brief Sound asset that defines how audio playback for door opening should behave.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	class USoundCue* door_opening_sound_;
};
