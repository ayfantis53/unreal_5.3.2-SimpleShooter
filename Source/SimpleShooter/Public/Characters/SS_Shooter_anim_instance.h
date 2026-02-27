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
#include "Animation/AnimInstance.h"
#include "SS_Shooter_anim_instance.generated.h"


class ASS_Shooter_character;

/**
 *	Animation class to control players visual movements
 */
UCLASS(Abstract)
class SIMPLESHOOTER_API USS_Shooter_anim_instance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	/// @brief Updates animation properties, like bone rotations & positions, based on current animation data & input.
	/// @param delta_time Time taken between the frames of the gameplay can differ.
	UFUNCTION(BlueprintCallable)
	void update_animation_properties(float delta_time);

protected:
	/// @brief allows us to handle initialization of various properties on our animation instance.
	virtual auto NativeInitializeAnimation() -> void override;

	/// @brief Controls player characters lean when changing directions.
	/// @param delta_time Time taken between the frames of the gameplay can differ.
	auto lean(float delta_time) -> void;

	/// @brief Controls player characters rotation when changing directions at no speed.
	auto turn_in_place() -> void;

private:
	/* --------------------- REFERENCES --------------------- */

	/// @brief Reference to shooter character player.
	UPROPERTY()
	ASS_Shooter_character* shooter_character_ref_;

	/* ---------------- ANIMATION VARIABLES ----------------- */

	//// TURN IN PLACE VARIABLES  ////

	/// @brief The amount of sideways rotation character does.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TurnInPlace", meta = (AllowPrivateAccess = "true"))
	float tip_character_yaw_;

	/// @brief The amount of the last frame of sideways rotation character does. 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TurnInPlace", meta = (AllowPrivateAccess = "true"))
	float tip_character_yaw_last_frame_;

	/// @brief Offset of character sideways rotation from original point.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TurnInPlace", meta = (AllowPrivateAccess = "true"))
	float root_yaw_offset_;

	/// @brief Is character turning at zero acceleration.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TurnInPlace", meta = (AllowPrivateAccess = "true"))
	bool b_turning_in_place_;

	//// LEANING WHILE RUNNING ////

	/// @brief Is it a full body action?
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TurnInPlace", meta = (AllowPrivateAccess = "true"))
	bool full_body_;

	/// @brief Amount of forward or backward rotation character is experiencing.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TurnInPlace", meta = (AllowPrivateAccess = "true"))
	float pitch_{ 0.f };

	/// @brief Rotation of character based on mouse for turn in place animation.
	FRotator character_rotation_;

	/// @brief Rotation of character in previous frame based on mouse for turn in place animation.
	FRotator character_rotation_last_frame_;

	/// @brief
	float rotation_curve_;

	/// @brief
	float rotation_curve_last_frame_;

	//// RUNNING ////

	/// @brief Used for different running animations.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float movement_offset_yaw_;

	/// @brief Used for different running animations.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float last_movement_offset_yaw_;

	/// @brief
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lean", meta = (AllowPrivateAccess = "true"))
	float yaw_delta_;

	/// @brief Reference to shooter character player.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float speed_;

	/// @brief Is character going from stop to run or run to stop.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool b_is_accelerating_;

	//// ACTIONS ////

	/// @brief Is character aiming weapon for aim pose.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool b_aiming_;

	/// @brief Is character jumping or falling off something?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool b_is_in_air_;
	
	/// @brief Is players health zero.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	bool b_is_dead_;
};
