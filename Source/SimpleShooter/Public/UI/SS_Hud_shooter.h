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
#include "GameFramework/HUD.h"
#include "SS_Hud_shooter.generated.h"


class ASS_Player_character;
class SSS_Widget_health_bar;

/**
 *	Main Players HUD for screen
 */
UCLASS()
class SIMPLESHOOTER_API ASS_Hud_shooter : public AHUD
{
	GENERATED_BODY()

public:
	/// @brief Sets hud default properties.
	ASS_Hud_shooter();

	/// @brief Gets health widget ref.
	/// @return Health widget ref.
	FORCEINLINE auto get_health_widget()  const -> TSharedPtr<SSS_Widget_health_bar> { return health_widget_ref_; }
	
protected:
	/// @brief The Main Draw loop for the hud. Gets called before any messaging.
	auto DrawHUD() -> void override;

private:
	/// @brief puts the health progress bar and symbol on screen.
	auto set_up_health_widget() -> void;

	/* --------------------- REFERENCES --------------------- */

	/// @brief reference to player character so we can update the health widget percentage.
	ASS_Player_character* player_character_ref_;

	/* -------------------- CROSS-HAIRS --------------------- */

	//// CROSSHAIR POINTERS ////

	/// @brief pointer to 2D image asset that provides visual information for cross hairs.
	UPROPERTY()
	UTexture* cross_hair_texture_;

	/// @brief Location on screen we display crosshairs.
	FVector2D crosshair_location_;

	//// CROSSHAIR LOCATION ////

	/// @brief Screen center position.
	FVector2D screen_center_;

	/// @brief Half height of crosshairs so we can center them on screen.
	float crosshair_half_height_{ 30.f };

	/// @brief Half width of crosshairs so we can center them on screen.
	float crosshair_half_width_{ 30.f };

	//// CROSSHAIR PATHS ////
	
	/// @brief location of 2D image asset that provides visual information for cross hairs.
	FString cross_hair_path_{ "Texture2D'/Game/Weapons/FX/Textures/T_HUD/Cross_Q_9.Cross_Q_9'" };

	/* ----------------------- HEALTH ---------------------- */

	//// WIDGETS ////

	/// @brief ptr to widget that holds the HUD overlay widget.
	TSharedPtr<SWidget> health_widget_container_;

	/// @brief HUD Overlay for Health and Weapons.
	TSharedPtr<SSS_Widget_health_bar> health_widget_ref_;

	/// @brief params for the health widget so we can make the FSlateBrush.
	UTexture2D* health_bar_texture_;

	/// @brief params for the health widget so we can make the FSlateBrush.
	UTexture2D* health_icon_texture_;

	//// PATHS TO WIDGETS ////
	
	/// @brief path to health bar full texture.
	const FString health_bar_full_path_{ "Texture2D'/Game/Weapons/FX/Textures/T_HUD/HeathBar_Full.HeathBar_Full'" };

	/// @brief path to health icon full texture.
	const FString health_icon_path_{ "Texture2D'/Game/Weapons/FX/Textures/T_HUD/HUD_Health_Icon.HUD_Health_Icon'" };
};
