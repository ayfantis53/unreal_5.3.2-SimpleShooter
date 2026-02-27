// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //
#include "FX/SS_Camera_shake_weapon_fire.h"


USS_Camera_shake_weapon_fire::USS_Camera_shake_weapon_fire()
{
	OscillationDuration                = 0.2f;
	OscillationBlendInTime             = 0.0f;
	OscillationBlendOutTime            = 0.15f;

	// RotOscillation Values.
	RotOscillation.Pitch.Amplitude     = 0.1f;
	RotOscillation.Pitch.Frequency     = 10.f;
	RotOscillation.Pitch.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
	RotOscillation.Pitch.Waveform      = EOscillatorWaveform::SineWave;

	RotOscillation.Yaw.Amplitude       = 0.f;
	RotOscillation.Yaw.Frequency       = 0.f;
	RotOscillation.Yaw.InitialOffset   = EInitialOscillatorOffset::EOO_OffsetRandom;
	RotOscillation.Yaw.Waveform        = EOscillatorWaveform::SineWave;

	RotOscillation.Roll.Amplitude      = 0.5f;
	RotOscillation.Roll.Frequency      = 30.f;
	RotOscillation.Roll.InitialOffset  = EInitialOscillatorOffset::EOO_OffsetRandom;
	RotOscillation.Roll.Waveform       = EOscillatorWaveform::SineWave;
}
