// ============================================================================== //
//							Unreal Engine version 5.3.2					  
// Simple Shooter 																  
// --------------	
// Developed by Andrew Yfantis. 											   
// https://github.com/ayfantis53
//   											   
// 2025 																	   
// ============================================================================== //
#include "FX/SS_Camera_shake_launcher.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(spawn_launcher_shake_test, "UEUnitTests.FX.LauncherShake.SpawnLauncherShake", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto spawn_launcher_shake_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // // Create a new USS_Camera_shake_launcher instance.
    USS_Camera_shake_launcher* shake = NewObject<USS_Camera_shake_launcher>();

    //// TEST ////

    // Verify the values.
    TestEqual("OscillationDuration correct",                shake->OscillationDuration,                0.60f);
    TestEqual("OscillationBlendInTime correct",             shake->OscillationBlendInTime,             0.10f);
    TestEqual("OscillationBlendOutTime correct",            shake->OscillationBlendOutTime,            0.20f);

    TestEqual("RotOscillation.Pitch.Amplitude correct",     shake->RotOscillation.Pitch.Amplitude,     3.0f);
    TestEqual("RotOscillation.Pitch.Frequency correct",     shake->RotOscillation.Pitch.Frequency,     10.f);
    TestEqual("RotOscillation.Pitch.InitialOffset correct", shake->RotOscillation.Pitch.InitialOffset, EInitialOscillatorOffset::EOO_OffsetRandom);
    TestEqual("RotOscillation.Pitch.Waveform correct",      shake->RotOscillation.Pitch.Waveform ,     EOscillatorWaveform::SineWave);

    TestEqual("RotOscillation.Yaw.Amplitude correct",       shake->RotOscillation.Yaw.Amplitude,       1.0f );
    TestEqual("RotOscillation.Yaw.Frequency correct",       shake->RotOscillation.Yaw.Frequency,       10.0f);
    TestEqual("RotOscillation.Yaw.InitialOffset correct",   shake->RotOscillation.Yaw.InitialOffset,   EInitialOscillatorOffset::EOO_OffsetRandom);
    TestEqual("RotOscillation.Yaw.Waveform correct",        shake->RotOscillation.Yaw.Waveform,        EOscillatorWaveform::SineWave);

    TestEqual("RotOscillation.Roll.Amplitude correct",      shake->RotOscillation.Roll.Amplitude,      0.0f);
    TestEqual("RotOscillation.Roll.Frequency correct",      shake->RotOscillation.Roll.Frequency,      0.0f);
    TestEqual("RotOscillation.Roll.InitialOffset correct",  shake->RotOscillation.Roll.InitialOffset,  EInitialOscillatorOffset::EOO_OffsetRandom);
    TestEqual("RotOscillation.Roll.Waveform correct",       shake->RotOscillation.Roll.Waveform,       EOscillatorWaveform::SineWave);
    
    TestEqual("LocOscillation.X.Amplitude correct",         shake->LocOscillation.X.Amplitude,         0.0f);
    TestEqual("LocOscillation.X.Frequency correct",         shake->LocOscillation.X.Frequency,         0.0f);
    TestEqual("LocOscillation.X.InitialOffset correct",     shake->LocOscillation.X.InitialOffset,     EInitialOscillatorOffset::EOO_OffsetRandom);
    TestEqual("LocOscillation.X.Waveform correct",          shake->LocOscillation.X.Waveform,          EOscillatorWaveform::SineWave);

    TestEqual("LocOscillation.Y.Amplitude correct",         shake->LocOscillation.Y.Amplitude,        2.0f );
    TestEqual("LocOscillation.Y.Frequency correct",         shake->LocOscillation.Y.Frequency,        10.0f);
    TestEqual("LocOscillation.Y.InitialOffset correct",     shake->LocOscillation.Y.InitialOffset,    EInitialOscillatorOffset::EOO_OffsetRandom);
    TestEqual("LocOscillation.Y.Waveform correct",          shake->LocOscillation.Y.Waveform,         EOscillatorWaveform::SineWave);

    TestEqual("LocOscillation.Z.Amplitude correct",         shake->LocOscillation.Z.Amplitude,        2.0f );
    TestEqual("LocOscillation.Z.Frequency  correct",        shake->LocOscillation.Z.Frequency ,       10.0f);
    TestEqual("LocOscillation.Z.InitialOffset correct",     shake->LocOscillation.Z.InitialOffset,    EInitialOscillatorOffset::EOO_OffsetRandom);
    TestEqual("LocOscillation.Z.Waveform correct",          shake->LocOscillation.Z.Waveform,         EOscillatorWaveform::SineWave);

    //// FINISH ////
    
    // Clean up.
    shake->ConditionalBeginDestroy();
    // Finish test.
    return true;
}