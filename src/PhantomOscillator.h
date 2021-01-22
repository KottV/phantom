/*
  ==============================================================================

    PhantomOscillator.h
    Created: 20 Jan 2021 9:17:28pm
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

//==============================================================================
/**
*/
class PhantomOscillator 
{
public:
    //==========================================================================
    PhantomOscillator();
    ~PhantomOscillator();

    //==========================================================================
    void setPhaseDelta(float frequency, float sampleRate);

    //==========================================================================
    float evaluate();

private:
    //==========================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhantomOscillator)

    //==========================================================================
    void initWavetable();
    void clearWavetable();

    //==========================================================================
    Array<float> m_wavetable;
    const int k_wavetableSize = 1 << 10;

    float m_phase = 0.0;
    float m_phaseDelta = 0.0;
};