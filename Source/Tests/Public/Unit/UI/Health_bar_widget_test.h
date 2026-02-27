// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //#include "UI/SS_Widget_health_bar.h"


/**
 *  Test class suite to assist Unit testing for Health bar widget text
 */
class Health_bar_widget_test
{
public:
    /* --------------------- MEMBER VARS -------------------- */

    /// @brief Get lost game text.
    /// @return float.
    static auto get_full_percent(TSharedPtr<class SSS_Widget_health_bar> widget_ref) -> float
    {
        return widget_ref->percent_full_;
    }
};