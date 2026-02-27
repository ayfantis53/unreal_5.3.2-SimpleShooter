// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //
#include "UI/SS_Widget_health_bar.h"

// Unreal headers.
#include "SlateBasics.h"
#include "SlateOptMacros.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
auto SSS_Widget_health_bar::Construct(const FArguments& in_args) -> void
{
	// Slate setup of health bar from paths provided in hud.
	health_bar_brush_       = FSlateImageBrush(in_args._health_bar,
											   health_bar_size_,
											   health_bar_tint_green_);

	health_bar_empty_brush_ = FSlateImageBrush(in_args._health_bar,
											   health_bar_size_,
											   health_bar_tint_red_);
	// Slate setup of health icon from paths provided in hud.
	icon_brush_             = FSlateImageBrush(in_args._health_icon,
											   health_icon_size_,
											   health_icon_green_);

	ChildSlot
	[
		// Populate the widget.
		SNew(SConstraintCanvas)
			+ SConstraintCanvas::Slot()
			.Anchors(top_center_)
			.AutoSize(true)
			[
				SNew(SBox)
				.HeightOverride(health_bar_size_.Y)
				.WidthOverride(health_bar_size_.X)
				[
					// Progress Bar.
					SAssignNew(progress_bar_ref, SProgressBar)
						.BarFillType(EProgressBarFillType::LeftToRight)
						.BarFillStyle(EProgressBarFillStyle::Scale)
						.Percent(percent_full_)
						.FillColorAndOpacity(fill_color_green_)
						.BackgroundImage(&health_bar_empty_brush_)
						.FillImage(&health_bar_brush_)
						.BorderPadding(FVector2D(1, 1))
				]
			]
			+ SConstraintCanvas::Slot()
			.Anchors(top_center_)
			.Offset(health_icon_offset_)
			.AutoSize(true)
			[
				SNew(SBox)
				.HeightOverride(health_icon_size_.Y)
				.WidthOverride(health_icon_size_.X)
				[
					// Health Icon.
					SNew(SImage)
						.Image(&icon_brush_)
						.ColorAndOpacity(health_icon_green_)
				]
			]
	];
		
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

