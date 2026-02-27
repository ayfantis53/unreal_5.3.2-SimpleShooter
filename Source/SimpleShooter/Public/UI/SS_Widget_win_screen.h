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
#pragma once

// Unreal headers
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"


/**
 *	Slate widget that is design and function of Win game text  
 */
class SIMPLESHOOTER_API SSS_Widget_win_screen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSS_Widget_win_screen)
	{}
	SLATE_END_ARGS()

	/// @brief struct that contains the parameters passed to the widget during its construction.
	/// @param in_args struct that contains the parameters passed to the widget during its construction.
	auto Construct(const FArguments& in_args) -> void;

private:
	/* ------------------- TEXT PROPERTIES ------------------ */

	//// TEXT REFERENCES ////
	
	/// @brief Text for countdown display at start of game.
	TSharedPtr<STextBlock> win_text_;

	//// TEXT ////

	/// @brief Value for Start Game Text.
	FString win_game_text_{ "You WIN!!!" };

	//// STYLING ////

	/// @brief Size to set the win text.
	int font_size_{ 70 };

	/// @brief Color to set the win text.
	FLinearColor win_text_color_{ FLinearColor(0, 1.0, 0.087717, 1) };

	/// @brief Color to set the win text shadow.
	FLinearColor win_text_shadow_color_{ FLinearColor(0, 0, 0, 1) };

	/// @brief needed to set the widget text to Roboto.
	inline const static FString roboto_path_{ "Slate/Fonts/Roboto-Bold.ttf" };

	/* ----------------------- TESTING ---------------------- */
	
	/// @brief Test classes to unit test this Widget.
	friend class Win_screen_widget_test;
};
