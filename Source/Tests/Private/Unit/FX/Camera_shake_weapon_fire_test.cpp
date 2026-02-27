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
#include "FX/SS_Camera_shake_weapon_fire.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(spawn_weapon_shake_test, "UEUnitTests.FX.WeaponShake.SpawnWeaponShake", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto spawn_weapon_shake_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // // Create a new USS_Camera_shake_weapon_fire instance.
    USS_Camera_shake_weapon_fire* shake = NewObject<USS_Camera_shake_weapon_fire>();

    //// TEST ////

    // Verify the values.
    TestEqual("OscillationDuration correct",                shake->OscillationDuration,                0.2f );
    TestEqual("OscillationBlendInTime correct",             shake->OscillationBlendInTime,             0.0f );
    TestEqual("OscillationBlendOutTime correct",            shake->OscillationBlendOutTime,            0.15f);

    TestEqual("RotOscillation.Pitch.Amplitude correct",     shake->RotOscillation.Pitch.Amplitude,     0.10f);
    TestEqual("RotOscillation.Pitch.Frequency correct",     shake->RotOscillation.Pitch.Frequency,     10.0f);
    TestEqual("RotOscillation.Pitch.InitialOffset correct", shake->RotOscillation.Pitch.InitialOffset, EInitialOscillatorOffset::EOO_OffsetRandom);
    TestEqual("RotOscillation.Pitch.Waveform correct",      shake->RotOscillation.Pitch.Waveform ,     EOscillatorWaveform::SineWave);

    TestEqual("RotOscillation.Yaw.Amplitude correct",       shake->RotOscillation.Yaw.Amplitude,       0.0f );
    TestEqual("RotOscillation.Yaw.Frequency correct",       shake->RotOscillation.Yaw.Frequency,       0.0f );
    TestEqual("RotOscillation.Yaw.InitialOffset correct",   shake->RotOscillation.Yaw.InitialOffset,   EInitialOscillatorOffset::EOO_OffsetRandom);
    TestEqual("RotOscillation.Yaw.Waveform correct",        shake->RotOscillation.Yaw.Waveform,        EOscillatorWaveform::SineWave);

    TestEqual("RotOscillation.Roll.Amplitude correct",      shake->RotOscillation.Roll.Amplitude,      0.5f);
    TestEqual("RotOscillation.Roll.Frequency correct",      shake->RotOscillation.Roll.Frequency,      30.f);
    TestEqual("RotOscillation.Roll.InitialOffset correct",  shake->RotOscillation.Roll.InitialOffset,  EInitialOscillatorOffset::EOO_OffsetRandom);
    TestEqual("RotOscillation.Roll.Waveform correct",       shake->RotOscillation.Roll.Waveform,       EOscillatorWaveform::SineWave);
    
    //// FINISH ////
    
    // Clean up.
    shake->ConditionalBeginDestroy();
    // Finish test.
    return true;
}