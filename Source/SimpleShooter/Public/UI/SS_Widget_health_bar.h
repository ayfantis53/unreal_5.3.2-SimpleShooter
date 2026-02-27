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
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Layout/SConstraintCanvas.h"


/**
 *	Slate widget that is design and function of Players health bar  
 */
class SIMPLESHOOTER_API SSS_Widget_health_bar : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSS_Widget_health_bar):
		 _health_bar(nullptr),
		 _health_icon(nullptr)
	{}
		SLATE_ARGUMENT(UTexture2D*, health_bar)
		SLATE_ARGUMENT(UTexture2D*, health_icon)
	SLATE_END_ARGS()

	/// @brief struct that contains the parameters passed to the widget during its construction.
	/// @param in_args struct that contains the parameters passed to the widget during its construction.
	auto Construct(const FArguments& in_args) -> void;

	/// @brief Reference to SProgressbar so we can update percent of health bar.
	TSharedPtr<class SProgressBar> progress_bar_ref;

private:
	/* --------------------- HEALTH BAR --------------------- */

	//// BAR FULL IMAGE ////

	/// @brief Struct used to define how a health bar fill widget should be drawn.
	FSlateBrush health_bar_brush_;
	
	/// @brief Color of the full health bar.
	FLinearColor health_bar_tint_green_{ FLinearColor(0.f, 1.f, 0.147f, 1.f) };

	/// @brief full percent of players health default.
	float percent_full_{ 100.f };

	//// BAR EMPTY IMAGE ////

	/// @brief Struct used to define how a health bar empty widget should be drawn.
	FSlateBrush health_bar_empty_brush_;

	/// @brief Color of the empty health bar.
	FLinearColor health_bar_tint_red_{ FLinearColor(1.f, 0.0371f, 0.f, 0.543f) };

	/// @brief path to health icon full texture.
	FLinearColor fill_color_green_{ FLinearColor(0.08091f, 1.f, 0.162268, 1.f)};

	//// BAR DIMENSIONS ////

	/// @brief Screen center position.
	FAnchors top_center_{ FAnchors(0.5f, 0.1f, 0.5f, 0.1f) };

	/// @brief Size of Health Bar Image to be displayed on screen.
	FVector2D health_bar_size_{ FVector2D(1300.f, 200.f) };

	/* ------------------------ ICON ------------------------ */

	//// HEALTH ICON IMAGE ////

	/// @brief Struct used to define how a health icon widget should be drawn.
	FSlateBrush icon_brush_;

	/// @brief path to health icon full texture.
	FLinearColor health_icon_green_{ FLinearColor(0.353f, 1.f, 0.f, 1.f) };

	//// HEALTH ICON DIMENSIONS ////

	/// @brief Size of Health Icon Image to be displayed on screen.
	FVector2D health_icon_size_{ FVector2D(108.f, 108.f) };

	/// @brief Offset of Health Icon Image to be displayed on screen.
	FVector2D health_icon_offset_{ FVector2D(-520.f, -5.f) };

	/* ----------------------- TESTING ---------------------- */
	
	/// @brief Test classes to unit test this Component.
	friend class Health_bar_widget_test;
};
