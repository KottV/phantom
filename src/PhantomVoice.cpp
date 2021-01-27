/*
  ==============================================================================

    PhantomVoice.cpp
    Created: 20 Jan 2021 20:59:55
    Author:  Matthew Maxwell

  ==============================================================================
*/

#include "PhantomVoice.h"

#include "PhantomSound.h"
#include "PhantomUtils.h"

//==============================================================================
PhantomVoice::PhantomVoice(AudioProcessorValueTreeState& vts, dsp::ProcessSpec& ps)
    :   m_parameters(vts)
{
    m_ampEg = new PhantomEnvelopeGenerator(m_parameters, EnvelopeGeneratorType::AMP);
    m_phaseEg = new PhantomEnvelopeGenerator(m_parameters, EnvelopeGeneratorType::PHASE);
    m_filterEg = new PhantomEnvelopeGenerator(m_parameters, EnvelopeGeneratorType::FLTR);
    m_modEg = new PhantomEnvelopeGenerator(m_parameters, EnvelopeGeneratorType::MOD);

    m_osc = new PhantomOscillator(m_parameters);
    m_filter = new PhantomFilter(m_parameters, ps);
    m_amp = new PhantomAmplifier(m_parameters);
}

PhantomVoice::~PhantomVoice()
{
    m_ampEg = nullptr;
    m_phaseEg = nullptr;
    m_filterEg = nullptr;
    m_modEg = nullptr;
    
    m_osc = nullptr;
    m_filter = nullptr;
    m_amp = nullptr;
}

//==============================================================================
bool PhantomVoice::canPlaySound(SynthesiserSound* sound)
{
    return dynamic_cast<PhantomSound*> (sound) != nullptr;
}

void PhantomVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{ 
    m_midiNoteNumber = midiNoteNumber;
    m_osc->update(m_midiNoteNumber, getSampleRate());
    
    m_ampEg->setSampleRate(getSampleRate());
    m_ampEg->update();
    m_ampEg->noteOn();

    m_phaseEg->setSampleRate(getSampleRate());
    m_phaseEg->update();
    m_phaseEg->noteOn();

    m_filterEg->setSampleRate(getSampleRate());
    m_filterEg->update();
    m_filterEg->noteOn();

    m_modEg->setSampleRate(getSampleRate());
    m_modEg->update();
    m_modEg->noteOn();
}

void PhantomVoice::stopNote(float velocity, bool allowTailOff)
{
    m_ampEg->noteOff();
    m_phaseEg->noteOff();
    m_filterEg->noteOff();
    m_modEg->noteOff();

    clearCurrentNote();
}

//==============================================================================
void PhantomVoice::pitchWheelMoved(int newPitchWheel)
{

}

void PhantomVoice::controllerMoved(int controllerNumber, int newControllerValue) 
{

}

//==============================================================================
void PhantomVoice::renderNextBlock(AudioBuffer<float>& buffer, int startSample, int numSamples)
{
    m_ampEg->update();
    m_phaseEg->update();
    m_filterEg->update();
    m_modEg->update();

    m_osc->update(m_midiNoteNumber, getSampleRate());
    m_filter->update();

    for (int sample = startSample; sample < numSamples; sample++)
    {
        float ampEnvelope = m_ampEg->evaluate();
        float phaseEnvelope = m_phaseEg->evaluate();
        float filterEnvelope = m_filterEg->evaluate();
        float modEnvelope = m_modEg->evaluate();

        float oscValue = m_osc->evaluate(modEnvelope);
        float filterValue = m_filter->evaluate(oscValue, filterEnvelope);
        float ampValue = filterValue * ampEnvelope;

        for (int channel = 0; channel < buffer.getNumChannels(); channel++)
        {
            float oldSample = buffer.getSample(channel, sample);
            buffer.setSample(channel, sample, oldSample + filterValue);
        }
    }

    m_amp->apply(buffer);
}
