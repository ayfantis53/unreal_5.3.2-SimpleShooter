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

#include "UI/SS_Widget_win_screen.h"

// Unreal headers.
#include "SlateBasics.h"
#include "SlateOptMacros.h"
#include "Widgets/Layout/SConstraintCanvas.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
auto SSS_Widget_win_screen::Construct(const FArguments& in_args) -> void
{

	ChildSlot
	[
		// Populate the widget.
		SNew(SConstraintCanvas)
			+ SConstraintCanvas::Slot()
			.AutoSize(true)
			.Anchors(FAnchors(0.5, 0.5, 0.5, 0.5))
			.Offset(FVector2d(0, -100))
			[
				// Our text for widget.
				SAssignNew(win_text_, STextBlock)
					.Font(FSlateFontInfo(FPaths::EngineContentDir() / roboto_path_, font_size_))
					.ColorAndOpacity(win_text_color_)
					.ShadowColorAndOpacity(win_text_shadow_color_)
					.ShadowOffset(FVector2D(2.f, 2.f))
					.Text(FText::FromString(win_game_text_))
			]
	];

}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
