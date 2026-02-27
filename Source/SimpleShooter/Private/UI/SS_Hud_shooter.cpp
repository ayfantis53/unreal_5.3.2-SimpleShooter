// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //
#include "UI/SS_Hud_shooter.h"
#include "UI/SS_Widget_health_bar.h"

// Unreal headers
#include "SlateBasics.h"


ASS_Hud_shooter::ASS_Hud_shooter()
{
	// Set path to our muzzle flash particle system.
	static ConstructorHelpers::FObjectFinder<UTexture> cross_hair_texture_container(*cross_hair_path_);
	if (cross_hair_texture_container.Succeeded())
	{
		cross_hair_texture_ = cross_hair_texture_container.Object;
	}

	// Set textures of Health bar.
	static  ConstructorHelpers::FObjectFinder<UTexture2D> health_bar_container(*health_bar_full_path_);
	if (health_bar_container.Succeeded())
	{
		health_bar_texture_ = health_bar_container.Object;
	}
	static  ConstructorHelpers::FObjectFinder<UTexture2D> health_icon_container(*health_icon_path_);
	if (health_icon_container.Succeeded())
	{
		health_icon_texture_ = health_icon_container.Object;
	}

	set_up_health_widget();
}

auto ASS_Hud_shooter::DrawHUD() -> void
{
	// Get size of game viewport.
	const FVector2D viewport_size = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

	// Get center of the screen.
	screen_center_                = FVector2D((viewport_size.X / 2), (viewport_size.Y / 2));
	crosshair_location_.X         = screen_center_.X - crosshair_half_width_;
	crosshair_location_.Y         = screen_center_.Y - crosshair_half_height_;

	this->DrawTexture(cross_hair_texture_,
					  crosshair_location_.X,
					  crosshair_location_.Y,
					  64.f,
					  64.f,
					  0.f,
					  0.f,
					  1.f,
					  1.f);

	Super::DrawHUD();
}

auto ASS_Hud_shooter::set_up_health_widget() -> void
{
	// Draw Widget.
	if (GEngine && GEngine->GameViewport)
	{
		// Get viewport.
		UGameViewportClient* view_port = GEngine->GameViewport;

		// Initialize widget.
		health_widget_ref_ = SNew(SSS_Widget_health_bar).health_bar(health_bar_texture_).health_icon(health_icon_texture_);
		view_port->AddViewportWidgetContent(SAssignNew(health_widget_container_, SWeakWidget).PossiblyNullContent(health_widget_ref_));

		// Make widget seen on screen.
		health_widget_ref_->SetVisibility(EVisibility::Visible);
	}
}

