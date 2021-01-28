/*
  ==============================================================================

    PhantomPhasor.cpp
    Created: 27 Jan 2021 13:03:12
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomPhasor.h"

#include "PhantomUtils.h"

PhantomPhasor::PhantomPhasor(AudioProcessorValueTreeState& vts)
    :   m_parameters(vts)
{
    p_shape = m_parameters.getRawParameterValue(Consts::_PHASOR_SHAPE_PARAM_ID);
    p_egInt = m_parameters.getRawParameterValue(Consts::_PHASOR_EG_INT_PARAM_ID);
    p_lfoInt = m_parameters.getRawParameterValue(Consts::_PHASOR_LFO_INT_PARAM_ID);
}

PhantomPhasor::~PhantomPhasor()
{
    p_shape = nullptr;
    p_egInt = nullptr;
    p_lfoInt = nullptr;
}

//==========================================================================
float PhantomPhasor::apply(float oldPhase, float egMod, float lfoMod) noexcept
{
    float envelope = *p_egInt * egMod * (*p_lfoInt * -0.5f + 1.0f);
    float lfo = *p_lfoInt * (lfoMod * 0.5f + 0.5f) * (*p_egInt * -0.5f + 1.0f);
    float mod = envelope + lfo;

    oldPhase /= (float) Consts::_WAVETABLE_SIZE;

    float phasor = evaluate(oldPhase);
    float phase = (phasor * mod) + (oldPhase * (1.0f - mod));

    return phase * (float) Consts::_WAVETABLE_SIZE;
}

//==============================================================================
float PhantomPhasor::evaluate(float phase) noexcept
{
    switch((int) *p_shape)
    {
        default:
        case 0:
            return sawtooth(phase);
            break;
    }
}

float PhantomPhasor::sawtooth(float phase) noexcept
{
    float slope;

    float breakpoint = 0.01f;
    if(phase <= breakpoint)
    {
        slope = 0.5f / breakpoint;
        return slope * phase;
    }
    else
    {
        slope = 0.5f / (1.0f - breakpoint);
        return slope * (phase - breakpoint) + 0.5f;
    }
}