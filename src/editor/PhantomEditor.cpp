/*
  ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#include "PhantomEditor.h"

#include "../utils/PhantomUtils.h"

PhantomAudioProcessorEditor::PhantomAudioProcessorEditor(PhantomAudioProcessor& p, AudioProcessorValueTreeState& vts) : AudioProcessorEditor(&p), m_processor(p), m_parameters(vts)
{
    initLayoutVariables();

    m_phantomAmplifier = std::make_unique<PhantomAmplifierComponent>(vts);
    addAndMakeVisible(m_phantomAmplifier.get());

    m_phantomOscillators = std::make_unique<PhantomOscillatorComponent>(vts);
    addAndMakeVisible(m_phantomOscillators.get());

    m_phantomPhasors = std::make_unique<PhantomPhasorComponent>(vts);
    addAndMakeVisible(m_phantomPhasors.get());

    initMixerGui();
    initFilterGui();
    initLfoGui();
    initEgGui();

    m_phantomAnalyzer = std::make_unique<PhantomAnalyzerComponent>();
    addAndMakeVisible(m_phantomAnalyzer.get());

    m_phantomOscilloscope = std::make_unique<PhantomOscilloscopeComponent>();
    addAndMakeVisible(m_phantomOscilloscope.get());

    initPresetMenu();

    loadPresetFilePaths();

    initEditor();
}

PhantomAudioProcessorEditor::~PhantomAudioProcessorEditor()
{
    setLookAndFeel(nullptr);

    m_phantomAmplifier = nullptr;
    m_phantomOscillators = nullptr;
    m_phantomPhasors = nullptr;

    m_phantomAnalyzer = nullptr;
    m_phantomOscilloscope = nullptr;

    // TODO: Put these in respective component classes!

    m_mixerOscBalanceSliderAttachment = nullptr;
    m_mixerRingModSliderAttachment = nullptr;
    m_mixerNoiseSliderAttachment = nullptr;

    m_filterCutoffSliderAttachment = nullptr;
    m_filterResoSliderAttachment = nullptr;
    m_filterDriveSliderAttachment = nullptr;
    m_filterModeSliderAttachment = nullptr;
    m_filterEgModDepthSliderAttachment = nullptr;
    m_filterLfoModDepthSliderAttachment = nullptr;

    m_lfo01RateSliderAttachment = nullptr;
    m_lfo01ShapeSliderAttachment = nullptr;
    m_lfo02RateSliderAttachment = nullptr;
    m_lfo02ShapeSliderAttachment = nullptr;

    m_ampEgAtkSliderAttachment = nullptr;
    m_ampEgDecSliderAttachment = nullptr;
    m_ampEgSusSliderAttachment = nullptr;
    m_ampEgRelSliderAttachment = nullptr;

    m_phasorEgAtkSliderAttachment = nullptr;
    m_phasorEgDecSliderAttachment = nullptr;
    m_phasorEgSusSliderAttachment = nullptr;
    m_phasorEgRelSliderAttachment = nullptr;

    m_filterEgAtkSliderAttachment = nullptr;
    m_filterEgDecSliderAttachment = nullptr;
    m_filterEgSusSliderAttachment = nullptr;
    m_filterEgRelSliderAttachment = nullptr;

    m_modEgAtkSliderAttachment = nullptr;
    m_modEgDecSliderAttachment = nullptr;
    m_modEgSusSliderAttachment = nullptr;
    m_modEgRelSliderAttachment = nullptr;
}

void PhantomAudioProcessorEditor::initLayoutVariables()
{    
    m_textBoxWidth = 80;
    m_textBoxHeight = 20;
}

void PhantomAudioProcessorEditor::initMixerGui() 
{
    m_mixerOscBalanceSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_mixerOscBalanceSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_mixerOscBalanceSlider.setDoubleClickReturnValue(true, Consts::_MIXER_OSC_BAL_DEFAULT_VAL);
    m_mixerOscBalanceSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_MIXER_OSC_BAL_PARAM_ID, m_mixerOscBalanceSlider));
    addAndMakeVisible(&m_mixerOscBalanceSlider);
    m_mixerOscBalanceLabel.setText("Osc Balance", dontSendNotification);
    m_mixerOscBalanceLabel.setJustificationType(Justification::centred);
    m_mixerOscBalanceLabel.attachToComponent(&m_mixerOscBalanceSlider, false);
    addAndMakeVisible(&m_mixerOscBalanceLabel);
    m_mixerLabel.setText("Mixer", dontSendNotification);
    m_mixerLabel.setJustificationType(Justification::topLeft);
    m_mixerLabel.attachToComponent(&m_mixerOscBalanceSlider, false);
    addAndMakeVisible(&m_mixerLabel);

    m_mixerAmpGainSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_mixerAmpGainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_mixerAmpGainSlider.setDoubleClickReturnValue(true, Consts::_MIXER_AMP_GAIN_DEFAULT_VAL);
    m_mixerAmpGainSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_MIXER_AMP_GAIN_PARAM_ID, m_mixerAmpGainSlider));
    addAndMakeVisible(&m_mixerAmpGainSlider);
    m_mixerAmpGainLabel.setText("Amp Gain", dontSendNotification);
    m_mixerAmpGainLabel.setJustificationType(Justification::centred);
    m_mixerAmpGainLabel.attachToComponent(&m_mixerAmpGainSlider, false);
    addAndMakeVisible(&m_mixerAmpGainLabel);

    m_mixerRingModSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_mixerRingModSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_mixerRingModSlider.setDoubleClickReturnValue(true, Consts::_MIXER_RING_MOD_DEFAULT_VAL);
    m_mixerRingModSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_MIXER_RING_MOD_PARAM_ID, m_mixerRingModSlider));
    addAndMakeVisible(&m_mixerRingModSlider);
    m_mixerRingModLabel.setText("Ring Mod", dontSendNotification);
    m_mixerRingModLabel.setJustificationType(Justification::centred);
    m_mixerRingModLabel.attachToComponent(&m_mixerRingModSlider, false);
    addAndMakeVisible(&m_mixerRingModLabel);

    m_mixerNoiseSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_mixerNoiseSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_mixerNoiseSlider.setDoubleClickReturnValue(true, Consts::_MIXER_NOISE_DEFAULT_VAL);
    m_mixerNoiseSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_MIXER_NOISE_PARAM_ID, m_mixerNoiseSlider));
    addAndMakeVisible(&m_mixerNoiseSlider);
    m_mixerNoiseLabel.setText("Noise", dontSendNotification);
    m_mixerNoiseLabel.setJustificationType(Justification::bottomLeft);
    m_mixerNoiseLabel.attachToComponent(&m_mixerNoiseSlider, false);
    addAndMakeVisible(&m_mixerNoiseLabel);
}

void PhantomAudioProcessorEditor::initFilterGui() 
{
    m_filterCutoffSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterCutoffSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_filterCutoffSlider.setTextValueSuffix(" Hz");
    m_filterCutoffSlider.setDoubleClickReturnValue(true, Consts::_FLTR_CUTOFF_DEFAULT_VAL);
    m_filterCutoffSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_CUTOFF_PARAM_ID, m_filterCutoffSlider));
    addAndMakeVisible(&m_filterCutoffSlider);
    m_filterCutoffLabel.setText("Cutoff", dontSendNotification);
    m_filterCutoffLabel.setJustificationType(Justification::centred);
    m_filterCutoffLabel.attachToComponent(&m_filterCutoffSlider, false);
    addAndMakeVisible(&m_filterCutoffLabel);
    m_filterLabel.setText("Filter", dontSendNotification);
    m_filterLabel.setJustificationType(Justification::topLeft);
    m_filterLabel.attachToComponent(&m_filterCutoffSlider, false);
    addAndMakeVisible(&m_filterLabel);

    m_filterResoSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterResoSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_filterResoSlider.setTextValueSuffix(" Q");
    m_filterResoSlider.setDoubleClickReturnValue(true, Consts::_FLTR_RESO_DEFAULT_VAL);
    m_filterResoSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_RESO_PARAM_ID, m_filterResoSlider));
    addAndMakeVisible(&m_filterResoSlider);
    m_filterResoLabel.setText("Resonance", dontSendNotification);
    m_filterResoLabel.setJustificationType(Justification::centred);
    m_filterResoLabel.attachToComponent(&m_filterResoSlider, false);
    addAndMakeVisible(&m_filterResoLabel);

    m_filterDriveSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterDriveSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_filterDriveSlider.setDoubleClickReturnValue(true, Consts::_FLTR_DRIVE_DEFAULT_VAL);
    m_filterDriveSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_DRIVE_PARAM_ID, m_filterDriveSlider));
    addAndMakeVisible(&m_filterDriveSlider);
    m_filterDriveLabel.setText("Drive", dontSendNotification);
    m_filterDriveLabel.setJustificationType(Justification::centred);
    m_filterDriveLabel.attachToComponent(&m_filterDriveSlider, false);
    addAndMakeVisible(&m_filterDriveLabel);

    m_filterModeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterModeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_filterModeSlider.setDoubleClickReturnValue(true, Consts::_FLTR_MODE_DEFAULT_VAL);
    m_filterModeSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_MODE_PARAM_ID, m_filterModeSlider));
    addAndMakeVisible(&m_filterModeSlider);
    m_filterModeLabel.setText("Mode", dontSendNotification);
    m_filterModeLabel.setJustificationType(Justification::centred);
    m_filterModeLabel.attachToComponent(&m_filterModeSlider, false);
    addAndMakeVisible(&m_filterModeLabel);

    m_filterEgModDepthSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterEgModDepthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_filterEgModDepthSlider.setDoubleClickReturnValue(true, Consts::_FLTR_EG_MOD_DEPTH_DEFAULT_VAL);
    m_filterEgModDepthSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_EG_MOD_DEPTH_PARAM_ID, m_filterEgModDepthSlider));
    addAndMakeVisible(&m_filterEgModDepthSlider);
    m_filterEgModDepthLabel.setText("EG Depth", dontSendNotification);
    m_filterEgModDepthLabel.setJustificationType(Justification::bottomLeft);
    m_filterEgModDepthLabel.attachToComponent(&m_filterEgModDepthSlider, false);
    addAndMakeVisible(&m_filterEgModDepthLabel);

    m_filterLfoModDepthSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterLfoModDepthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_filterLfoModDepthSlider.setDoubleClickReturnValue(true, Consts::_FLTR_LFO_MOD_DEPTH_DEFAULT_VAL);
    m_filterLfoModDepthSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_LFO_MOD_DEPTH_PARAM_ID, m_filterLfoModDepthSlider));
    addAndMakeVisible(&m_filterLfoModDepthSlider);
    m_filterLfoModDepthLabel.setText("LFO 1 Depth", dontSendNotification);
    m_filterLfoModDepthLabel.setJustificationType(Justification::bottomLeft);
    m_filterLfoModDepthLabel.attachToComponent(&m_filterLfoModDepthSlider, false);
    addAndMakeVisible(&m_filterLfoModDepthLabel);
}

void PhantomAudioProcessorEditor::initLfoGui()
{
    m_lfo01RateSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_lfo01RateSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_lfo01RateSlider.setTextValueSuffix(" Hz");
    m_lfo01RateSlider.setDoubleClickReturnValue(true, Consts::_LFO_01_RATE_DEFAULT_VAL);
    m_lfo01RateSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_LFO_01_RATE_PARAM_ID, m_lfo01RateSlider));
    addAndMakeVisible(&m_lfo01RateSlider);
    m_lfo01RateLabel.setText("Rate", dontSendNotification);
    m_lfo01RateLabel.setJustificationType(Justification::centred);
    m_lfo01RateLabel.attachToComponent(&m_lfo01RateSlider, false);
    addAndMakeVisible(&m_lfo01RateLabel);
    m_lfoLabel.setText("LFOs", dontSendNotification);
    m_lfoLabel.setJustificationType(Justification::topLeft);
    m_lfoLabel.attachToComponent(&m_lfo01RateSlider, false);
    addAndMakeVisible(&m_lfoLabel);

    m_lfo01ShapeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_lfo01ShapeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_lfo01ShapeSlider.setDoubleClickReturnValue(true, Consts::_LFO_01_SHAPE_DEFAULT_VAL);
    m_lfo01ShapeSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_LFO_01_SHAPE_PARAM_ID, m_lfo01ShapeSlider));
    addAndMakeVisible(&m_lfo01ShapeSlider);
    m_lfo01ShapeLabel.setText("Shape", dontSendNotification);
    m_lfo01ShapeLabel.setJustificationType(Justification::centred);
    m_lfo01ShapeLabel.attachToComponent(&m_lfo01ShapeSlider, false);
    addAndMakeVisible(&m_lfo01ShapeLabel);

    m_lfo02RateSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_lfo02RateSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_lfo02RateSlider.setTextValueSuffix(" Hz");
    m_lfo02RateSlider.setDoubleClickReturnValue(true, Consts::_LFO_01_RATE_DEFAULT_VAL);
    m_lfo02RateSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_LFO_02_RATE_PARAM_ID, m_lfo02RateSlider));
    addAndMakeVisible(&m_lfo02RateSlider);

    m_lfo02ShapeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_lfo02ShapeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_lfo02ShapeSlider.setDoubleClickReturnValue(true, Consts::_LFO_01_SHAPE_DEFAULT_VAL);
    m_lfo02ShapeSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_LFO_02_SHAPE_PARAM_ID, m_lfo02ShapeSlider));
    addAndMakeVisible(&m_lfo02ShapeSlider);
}

void PhantomAudioProcessorEditor::initEgGui() 
{
    m_ampEgAtkSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_ampEgAtkSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_ampEgAtkSlider.setTextValueSuffix(" s");
    m_ampEgAtkSlider.setDoubleClickReturnValue(true, Consts::_AMP_EG_ATK_DEFAULT_VAL);
    m_ampEgAtkSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_AMP_EG_ATK_PARAM_ID, m_ampEgAtkSlider));
    addAndMakeVisible(&m_ampEgAtkSlider);
    m_ampEgAtkLabel.setText("Atk", dontSendNotification);
    m_ampEgAtkLabel.setJustificationType(Justification::centred);
    m_ampEgAtkLabel.attachToComponent(&m_ampEgAtkSlider, false);
    addAndMakeVisible(&m_ampEgAtkLabel);
    m_ampEgLabel.setText("AMP", dontSendNotification);
    m_ampEgLabel.setJustificationType(Justification::right);
    m_ampEgLabel.attachToComponent(&m_ampEgAtkSlider, true);
    addAndMakeVisible(&m_ampEgLabel);

    m_ampEgDecSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_ampEgDecSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_ampEgDecSlider.setTextValueSuffix(" s");
    m_ampEgDecSlider.setDoubleClickReturnValue(true, Consts::_AMP_EG_DEC_DEFAULT_VAL);
    m_ampEgDecSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_AMP_EG_DEC_PARAM_ID, m_ampEgDecSlider));
    addAndMakeVisible(&m_ampEgDecSlider);
    m_ampEgDecLabel.setText("Dec", dontSendNotification);
    m_ampEgDecLabel.setJustificationType(Justification::centred);
    m_ampEgDecLabel.attachToComponent(&m_ampEgDecSlider, false);
    addAndMakeVisible(&m_ampEgDecLabel);

    m_ampEgSusSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_ampEgSusSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_ampEgSusSlider.setTextValueSuffix(" dB");
    m_ampEgSusSlider.setDoubleClickReturnValue(true, Consts::_AMP_EG_SUS_DEFAULT_VAL);
    m_ampEgSusSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_AMP_EG_SUS_PARAM_ID, m_ampEgSusSlider));
    addAndMakeVisible(&m_ampEgSusSlider);
    m_ampEgSusLabel.setText("Sus", dontSendNotification);
    m_ampEgSusLabel.setJustificationType(Justification::centred);
    m_ampEgSusLabel.attachToComponent(&m_ampEgSusSlider, false);
    addAndMakeVisible(&m_ampEgSusLabel);

    m_ampEgRelSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_ampEgRelSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_ampEgRelSlider.setTextValueSuffix(" s");
    m_ampEgRelSlider.setDoubleClickReturnValue(true, Consts::_AMP_EG_REL_DEFAULT_VAL);
    m_ampEgRelSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_AMP_EG_REL_PARAM_ID, m_ampEgRelSlider));
    addAndMakeVisible(&m_ampEgRelSlider);
    m_ampEgRelLabel.setText("Rel", dontSendNotification);
    m_ampEgRelLabel.setJustificationType(Justification::centred);
    m_ampEgRelLabel.attachToComponent(&m_ampEgRelSlider, false);
    addAndMakeVisible(&m_ampEgRelLabel);

    m_phasorEgAtkSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasorEgAtkSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_phasorEgAtkSlider.setTextValueSuffix(" s");
    m_phasorEgAtkSlider.setDoubleClickReturnValue(true, Consts::_PHASOR_EG_ATK_DEFAULT_VAL);
    m_phasorEgAtkSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_EG_ATK_PARAM_ID, m_phasorEgAtkSlider));
    addAndMakeVisible(&m_phasorEgAtkSlider);
    m_phasorEgAtkLabel.setText("Atk", dontSendNotification);
    m_phasorEgAtkLabel.setJustificationType(Justification::centred);
    m_phasorEgAtkLabel.attachToComponent(&m_phasorEgAtkSlider, false);
    addAndMakeVisible(&m_phasorEgAtkLabel);
    m_phasorEgLabel.setText("PHA", dontSendNotification);
    m_phasorEgLabel.setJustificationType(Justification::right);
    m_phasorEgLabel.attachToComponent(&m_phasorEgAtkSlider, true);
    addAndMakeVisible(&m_phasorEgLabel);

    m_phasorEgDecSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasorEgDecSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_phasorEgDecSlider.setTextValueSuffix(" s");
    m_phasorEgDecSlider.setDoubleClickReturnValue(true, Consts::_PHASOR_EG_DEC_DEFAULT_VAL);
    m_phasorEgDecSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_EG_DEC_PARAM_ID, m_phasorEgDecSlider));
    addAndMakeVisible(&m_phasorEgDecSlider);
    m_phasorEgDecLabel.setText("Dec", dontSendNotification);
    m_phasorEgDecLabel.setJustificationType(Justification::centred);
    m_phasorEgDecLabel.attachToComponent(&m_phasorEgDecSlider, false);
    addAndMakeVisible(&m_phasorEgDecLabel);

    m_phasorEgSusSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasorEgSusSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_phasorEgSusSlider.setTextValueSuffix(" dB");
    m_phasorEgSusSlider.setDoubleClickReturnValue(true, Consts::_PHASOR_EG_SUS_DEFAULT_VAL);
    m_phasorEgSusSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_EG_SUS_PARAM_ID, m_phasorEgSusSlider));
    addAndMakeVisible(&m_phasorEgSusSlider);
    m_phasorEgSusLabel.setText("Sus", dontSendNotification);
    m_phasorEgSusLabel.setJustificationType(Justification::centred);
    m_phasorEgSusLabel.attachToComponent(&m_phasorEgSusSlider, false);
    addAndMakeVisible(&m_phasorEgSusLabel);

    m_phasorEgRelSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_phasorEgRelSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_phasorEgRelSlider.setTextValueSuffix(" s");
    m_phasorEgRelSlider.setDoubleClickReturnValue(true, Consts::_PHASOR_EG_REL_DEFAULT_VAL);
    m_phasorEgRelSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_PHASOR_EG_REL_PARAM_ID, m_phasorEgRelSlider));
    addAndMakeVisible(&m_phasorEgRelSlider);
    m_phasorEgRelLabel.setText("Rel", dontSendNotification);
    m_phasorEgRelLabel.setJustificationType(Justification::centred);
    m_phasorEgRelLabel.attachToComponent(&m_phasorEgRelSlider, false);
    addAndMakeVisible(&m_phasorEgRelLabel);

    m_filterEgAtkSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterEgAtkSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_filterEgAtkSlider.setTextValueSuffix(" s");
    m_filterEgAtkSlider.setDoubleClickReturnValue(true, Consts::_FLTR_EG_ATK_DEFAULT_VAL);
    m_filterEgAtkSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_EG_ATK_PARAM_ID, m_filterEgAtkSlider));
    addAndMakeVisible(&m_filterEgAtkSlider);
    m_filterEgLabel.setText("FLTR", dontSendNotification);
    m_filterEgLabel.setJustificationType(Justification::right);
    m_filterEgLabel.attachToComponent(&m_filterEgAtkSlider, true);
    addAndMakeVisible(&m_filterEgLabel);

    m_filterEgDecSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterEgDecSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_filterEgDecSlider.setTextValueSuffix(" s");
    m_filterEgDecSlider.setDoubleClickReturnValue(true, Consts::_FLTR_EG_DEC_DEFAULT_VAL);
    m_filterEgDecSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_EG_DEC_PARAM_ID, m_filterEgDecSlider));
    addAndMakeVisible(&m_filterEgDecSlider);

    m_filterEgSusSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterEgSusSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_filterEgSusSlider.setTextValueSuffix(" dB");
    m_filterEgSusSlider.setDoubleClickReturnValue(true, Consts::_FLTR_EG_SUS_DEFAULT_VAL);
    m_filterEgSusSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_EG_SUS_PARAM_ID, m_filterEgSusSlider));
    addAndMakeVisible(&m_filterEgSusSlider);

    m_filterEgRelSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_filterEgRelSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_filterEgRelSlider.setTextValueSuffix(" s");
    m_filterEgRelSlider.setDoubleClickReturnValue(true, Consts::_FLTR_EG_REL_DEFAULT_VAL);
    m_filterEgRelSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_FLTR_EG_REL_PARAM_ID, m_filterEgRelSlider));
    addAndMakeVisible(&m_filterEgRelSlider);

    m_modEgAtkSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_modEgAtkSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_modEgAtkSlider.setTextValueSuffix(" s");
    m_modEgAtkSlider.setDoubleClickReturnValue(true, Consts::_MOD_EG_ATK_DEFAULT_VAL);
    m_modEgAtkSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_MOD_EG_ATK_PARAM_ID, m_modEgAtkSlider));
    addAndMakeVisible(&m_modEgAtkSlider);
    m_modEgLabel.setText("MOD", dontSendNotification);
    m_modEgLabel.setJustificationType(Justification::right);
    m_modEgLabel.attachToComponent(&m_modEgAtkSlider, true);
    addAndMakeVisible(&m_modEgLabel);

    m_modEgDecSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_modEgDecSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_modEgDecSlider.setTextValueSuffix(" s");
    m_modEgDecSlider.setDoubleClickReturnValue(true, Consts::_MOD_EG_DEC_DEFAULT_VAL);
    m_modEgDecSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_MOD_EG_DEC_PARAM_ID, m_modEgDecSlider));
    addAndMakeVisible(&m_modEgDecSlider);

    m_modEgSusSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_modEgSusSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_modEgSusSlider.setTextValueSuffix(" dB");
    m_modEgSusSlider.setDoubleClickReturnValue(true, Consts::_MOD_EG_SUS_DEFAULT_VAL);
    m_modEgSusSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_MOD_EG_SUS_PARAM_ID, m_modEgSusSlider));
    addAndMakeVisible(&m_modEgSusSlider);

    m_modEgRelSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    m_modEgRelSlider.setTextBoxStyle(Slider::TextBoxBelow, false, m_textBoxWidth, m_textBoxHeight);
    m_modEgRelSlider.setTextValueSuffix(" s");
    m_modEgRelSlider.setDoubleClickReturnValue(true, Consts::_MOD_EG_REL_DEFAULT_VAL);
    m_modEgRelSliderAttachment.reset(new SliderAttachment(m_parameters, Consts::_MOD_EG_REL_PARAM_ID, m_modEgRelSlider));
    addAndMakeVisible(&m_modEgRelSlider);
}

void PhantomAudioProcessorEditor::initPresetMenu()
{
    m_presetLabel.setText("PRESET: ", dontSendNotification);
    m_presetLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&m_presetLabel);

    m_presetButton.setButtonText(m_processor.m_presetName);
    m_presetButton.setColour(TextButton::buttonColourId, Consts::_STROKE_COLOUR);
    m_presetButton.setColour(TextButton::buttonOnColourId, Consts::_FILL_START_COLOUR);
    addAndMakeVisible(&m_presetButton);
    m_presetButton.onClick = [this](){
        PopupMenu menu;

        menu.addItem(PopupMenu::Item("Copy to clipboard")
            .setAction([this](){
                SystemClipboard::copyTextToClipboard(*m_processor.saveStateToText());
            })
        );
        menu.addItem(PopupMenu::Item("Paste from clipboard")
            .setAction([this](){
                m_processor.loadStateFromText(SystemClipboard::getTextFromClipboard());

                resetGui();
            })
        );

        menu.addSeparator();

        menu.addItem(PopupMenu::Item("Initialize")
            .setAction([this](){
                m_processor.resetState();
                
                resetParameters();
                resetGui();
            })
        );
        menu.addItem(PopupMenu::Item("Save as")
            .setAction([this](){
                String presetDirPath = File::getSpecialLocation(File::userApplicationDataDirectory).getFullPathName()
                    + "/Black Box DSP/Phantom/Presets";
                FileChooser browser("Save as ...", presetDirPath, "*.xml");

                if(browser.browseForFileToSave(true))
                {
                    File res = browser.getResult();
                    m_processor.saveStateToFile(res);

                    loadPresetFilePaths();
                    setPresetIdx();
                    resetGui();
                }
            })
        );

        menu.addSeparator();

        menu.addSectionHeader("Presets");

        addPresetsToMenu(menu);

        menu.showMenu(PopupMenu::Options().withParentComponent(this));
    };

    m_presetLeftButton.setButtonText("<");
    m_presetLeftButton.setColour(TextButton::buttonColourId, Consts::_STROKE_COLOUR);
    m_presetLeftButton.setColour(TextButton::buttonOnColourId, Consts::_FILL_START_COLOUR);
    addAndMakeVisible(&m_presetLeftButton);
    m_presetLeftButton.onClick = [this](){
        m_presetIdx--;
        loadPresetFileAtIndex();
    };

    m_presetRightButton.setButtonText(">");
    m_presetRightButton.setColour(TextButton::buttonColourId, Consts::_STROKE_COLOUR);
    m_presetRightButton.setColour(TextButton::buttonOnColourId, Consts::_FILL_START_COLOUR);
    addAndMakeVisible(&m_presetRightButton);
    m_presetRightButton.onClick = [this](){
        m_presetIdx++;
        loadPresetFileAtIndex();
    };
}

void PhantomAudioProcessorEditor::initEditor()
{
    setLookAndFeel(&m_lookAndFeel);

    float ratio = 16.0f / 9.0f;
    setResizable(true, true);
    setResizeLimits(720 * ratio, 720, 1280 * ratio, 1280);
    getConstrainer()->setFixedAspectRatio(ratio);
    setSize(720 * ratio, 720);
}

void PhantomAudioProcessorEditor::addPresetsToMenu(PopupMenu& menu)
{
    String previousTypeDir = String("");
    PopupMenu typeDirSubMenu;

    for(File pf : m_processor.getPresetFiles())
    {
        if(previousTypeDir.isEmpty())
            previousTypeDir = pf.getParentDirectory().getFileName();
        
        String typeDir = String(pf.getParentDirectory().getFileName());
        if(!previousTypeDir.equalsIgnoreCase(typeDir))
        {
            menu.addSubMenu(previousTypeDir, typeDirSubMenu);
            typeDirSubMenu.clear();
        }

        previousTypeDir = String(typeDir);

        String presetName = String(pf.getFileNameWithoutExtension());
        typeDirSubMenu.addItem(
            PopupMenu::Item(presetName)
            .setEnabled(!presetName.equalsIgnoreCase(m_processor.m_presetName))
            .setAction([this, pf](){
                File presetFile = File(pf.getFullPathName());
                m_processor.loadStateFromFile(presetFile);

                setPresetIdx();
                resetGui();
            })
        );
    }

    menu.addSubMenu(previousTypeDir, typeDirSubMenu);
}


void PhantomAudioProcessorEditor::loadPresetFilePaths()
{
    m_presetFilePaths.clearQuick();

    for(File pf : m_processor.getPresetFiles())
        m_presetFilePaths.add(pf.getFullPathName());
}

void PhantomAudioProcessorEditor::loadPresetFileAtIndex()
{

    if(m_presetIdx >= -4 && m_presetIdx <= -2)
    {
        int previousIdx = m_presetIdx;

        if(!setPresetIdx())
            m_presetIdx = 0;
        else 
            if(previousIdx == -4)
                m_presetIdx--;
            else
                m_presetIdx++;
    }

    if(m_presetIdx < 0)
        m_presetIdx = m_presetFilePaths.size() - 1;
    else if(m_presetIdx >= m_presetFilePaths.size())
        m_presetIdx = 0;

    File file = File(m_presetFilePaths[m_presetIdx]);
    m_processor.loadStateFromFile(file);

    resetGui();
}

bool PhantomAudioProcessorEditor::setPresetIdx()
{
    int count = 0;

    for(File pf : m_processor.getPresetFiles())
    {
        String presetName = pf.getFileNameWithoutExtension();
        if(presetName == m_processor.m_presetName)
        {
            m_presetIdx = count;

            return true;
        }

        count++;
    }

    DBG(m_presetIdx);

    return false;
}

void PhantomAudioProcessorEditor::resetGui()
{
    m_presetButton.setButtonText(m_processor.m_presetName);
}

void PhantomAudioProcessorEditor::resetParameters()
{
    m_phantomAmplifier->reset();
    m_phantomOscillators->reset();
    m_phantomPhasors->reset();

    m_mixerOscBalanceSlider.setValue(Consts::_MIXER_OSC_BAL_DEFAULT_VAL);
    m_mixerAmpGainSlider.setValue(Consts::_MIXER_AMP_GAIN_DEFAULT_VAL);
    m_mixerRingModSlider.setValue(Consts::_MIXER_RING_MOD_DEFAULT_VAL);
    m_mixerNoiseSlider.setValue(Consts::_MIXER_NOISE_DEFAULT_VAL);

    m_filterCutoffSlider.setValue(Consts::_FLTR_CUTOFF_DEFAULT_VAL);
    m_filterResoSlider.setValue(Consts::_FLTR_RESO_DEFAULT_VAL);
    m_filterDriveSlider.setValue(Consts::_FLTR_DRIVE_DEFAULT_VAL);
    m_filterModeSlider.setValue(Consts::_FLTR_MODE_DEFAULT_VAL);
    m_filterEgModDepthSlider.setValue(Consts::_FLTR_EG_MOD_DEPTH_DEFAULT_VAL);
    m_filterLfoModDepthSlider.setValue(Consts::_FLTR_LFO_MOD_DEPTH_DEFAULT_VAL);

    m_lfo01RateSlider.setValue(Consts::_LFO_01_RATE_DEFAULT_VAL);
    m_lfo01ShapeSlider.setValue(Consts::_LFO_01_SHAPE_DEFAULT_VAL);
    m_lfo02RateSlider.setValue(Consts::_LFO_02_RATE_DEFAULT_VAL);
    m_lfo02ShapeSlider.setValue(Consts::_LFO_02_SHAPE_DEFAULT_VAL);

    m_ampEgAtkSlider.setValue(Consts::_AMP_EG_ATK_DEFAULT_VAL);
    m_ampEgDecSlider.setValue(Consts::_AMP_EG_DEC_DEFAULT_VAL);
    m_ampEgSusSlider.setValue(Consts::_AMP_EG_SUS_DEFAULT_VAL);
    m_ampEgRelSlider.setValue(Consts::_AMP_EG_REL_DEFAULT_VAL);

    m_filterEgAtkSlider.setValue(Consts::_FLTR_EG_ATK_DEFAULT_VAL);
    m_filterEgDecSlider.setValue(Consts::_FLTR_EG_DEC_DEFAULT_VAL);
    m_filterEgSusSlider.setValue(Consts::_FLTR_EG_SUS_DEFAULT_VAL);
    m_filterEgRelSlider.setValue(Consts::_FLTR_EG_REL_DEFAULT_VAL);

    m_phasorEgAtkSlider.setValue(Consts::_PHASOR_EG_ATK_DEFAULT_VAL);
    m_phasorEgDecSlider.setValue(Consts::_PHASOR_EG_DEC_DEFAULT_VAL);
    m_phasorEgSusSlider.setValue(Consts::_PHASOR_EG_SUS_DEFAULT_VAL);
    m_phasorEgRelSlider.setValue(Consts::_PHASOR_EG_REL_DEFAULT_VAL);

    m_modEgAtkSlider.setValue(Consts::_MOD_EG_ATK_DEFAULT_VAL);
    m_modEgDecSlider.setValue(Consts::_MOD_EG_DEC_DEFAULT_VAL);
    m_modEgSusSlider.setValue(Consts::_MOD_EG_SUS_DEFAULT_VAL);
    m_modEgRelSlider.setValue(Consts::_MOD_EG_REL_DEFAULT_VAL);
}

void PhantomAudioProcessorEditor::paint(Graphics& g)
{
    resetGui();

    g.fillAll(Colour::fromRGBA(2, 8, 8, 255));
    g.setColour(Colours::white);
    g.setFont(12.0f);
}

void PhantomAudioProcessorEditor::resized()
{
    Rectangle<int> canvas = getLocalBounds();

    const int margin = canvas.getWidth() / 60;
    canvas.removeFromTop(margin);
    canvas.removeFromRight(margin);
    canvas.removeFromBottom(margin);
    canvas.removeFromLeft(margin);

    const int width = canvas.getWidth();
    const int height = canvas.getHeight();
    const int sectionHeight = (height - (margin * 6)) / 4;

    const int topKnobWidth = (width - margin) / 7;
    Rectangle<int> topArea = canvas.removeFromTop(sectionHeight);
    canvas.removeFromTop(margin);

    m_phantomAmplifier->update(margin, topKnobWidth, topArea.removeFromLeft(topKnobWidth));
    topArea.removeFromLeft(margin);
    m_phantomOscillators->update(margin, topKnobWidth, topArea);

    const int middleTopKnobWidth = (width - (margin * 2)) / 7;
    Rectangle<int> middleTopArea = canvas.removeFromTop(sectionHeight + (margin * 2));
    canvas.removeFromTop(margin);

    Rectangle<int> analyzerArea = middleTopArea.removeFromLeft(middleTopKnobWidth * 2);
    m_phantomAnalyzer->update(analyzerArea);
    middleTopArea.removeFromLeft(margin);

    Rectangle<int> phasorArea = middleTopArea.removeFromLeft(middleTopKnobWidth * 3);
    middleTopArea.removeFromLeft(margin);

    Rectangle<int> presetArea = phasorArea.removeFromBottom(margin * 1.5);
    const int presetAreaWidth = presetArea.getWidth();
    m_presetLabel.setBounds(presetArea.removeFromLeft(presetAreaWidth * 0.3));
    m_presetButton.setBounds(presetArea.removeFromLeft(presetAreaWidth * 0.4));
    presetArea.removeFromLeft(presetAreaWidth * 0.1);
    m_presetLeftButton.setBounds(presetArea.removeFromLeft(presetAreaWidth * 0.1));
    m_presetRightButton.setBounds(presetArea);
    phasorArea.removeFromBottom(margin * 0.5);

    m_phantomPhasors->update(margin, middleTopKnobWidth, phasorArea);

    Rectangle<int> oscilloscopeArea = middleTopArea;
    m_phantomOscilloscope->update(oscilloscopeArea);

    const int middleBottomKnobWidth = (width - (margin * 2)) / 7;
    Rectangle<int> middleBottomArea = canvas.removeFromTop(sectionHeight);
    canvas.removeFromTop(margin);

    Rectangle<int> mixerArea = middleBottomArea.removeFromLeft(middleBottomKnobWidth * 2);
    middleBottomArea.removeFromLeft(margin);

    Rectangle<int> mixerTopArea = mixerArea.removeFromTop(mixerArea.getHeight() / 2);
    m_mixerOscBalanceSlider.setBounds(mixerTopArea.removeFromLeft(middleTopKnobWidth));
    m_mixerRingModSlider.setBounds(mixerTopArea);

    Rectangle<int> mixerBottomArea = mixerArea;
    m_mixerAmpGainSlider.setBounds(mixerBottomArea.removeFromLeft(middleTopKnobWidth));
    m_mixerNoiseSlider.setBounds(mixerBottomArea);

    Rectangle<int> filterArea = middleBottomArea.removeFromLeft(middleBottomKnobWidth * 3);
    middleBottomArea.removeFromLeft(margin);

    Rectangle<int> filterTopArea = filterArea.removeFromTop(filterArea.getHeight() / 2);
    m_filterCutoffSlider.setBounds(filterTopArea.removeFromLeft(middleBottomKnobWidth));
    m_filterResoSlider.setBounds(filterTopArea.removeFromLeft(middleBottomKnobWidth));
    m_filterDriveSlider.setBounds(filterTopArea);

    Rectangle<int> filterBottomArea = filterArea;
    m_filterModeSlider.setBounds(filterBottomArea.removeFromLeft(middleBottomKnobWidth));
    m_filterEgModDepthSlider.setBounds(filterBottomArea.removeFromLeft(middleBottomKnobWidth));
    m_filterLfoModDepthSlider.setBounds(filterBottomArea);

    Rectangle<int> lfoArea = middleBottomArea.removeFromLeft(middleBottomKnobWidth * 2);
    Rectangle<int> lfoTopArea = lfoArea.removeFromTop(lfoArea.getHeight() / 2);
    m_lfo01RateSlider.setBounds(lfoTopArea.removeFromLeft(middleBottomKnobWidth));
    m_lfo01ShapeSlider.setBounds(lfoTopArea);

    Rectangle<int> lfoBottomArea = lfoArea;
    m_lfo02RateSlider.setBounds(lfoBottomArea.removeFromLeft(middleBottomKnobWidth));
    m_lfo02ShapeSlider.setBounds(lfoBottomArea);

    const int bottomKnobWidth = (width - (margin * 2)) / 8;
    Rectangle<int> bottomArea = canvas;

    Rectangle<int> bottomTopArea = bottomArea.removeFromTop(bottomArea.getHeight() / 2);
    Rectangle<int> ampEgArea = bottomTopArea.removeFromLeft(bottomKnobWidth * 4);
    bottomTopArea.removeFromLeft(margin);
    m_ampEgAtkSlider.setBounds(ampEgArea.removeFromLeft(bottomKnobWidth));
    m_ampEgDecSlider.setBounds(ampEgArea.removeFromLeft(bottomKnobWidth));
    m_ampEgSusSlider.setBounds(ampEgArea.removeFromLeft(bottomKnobWidth));
    m_ampEgRelSlider.setBounds(ampEgArea.removeFromLeft(bottomKnobWidth));

    Rectangle<int> phasorEgArea = bottomTopArea;
    m_phasorEgAtkSlider.setBounds(phasorEgArea.removeFromLeft(bottomKnobWidth));
    m_phasorEgDecSlider.setBounds(phasorEgArea.removeFromLeft(bottomKnobWidth));
    m_phasorEgSusSlider.setBounds(phasorEgArea.removeFromLeft(bottomKnobWidth));
    m_phasorEgRelSlider.setBounds(phasorEgArea.removeFromLeft(bottomKnobWidth));

    Rectangle<int> bottomBottomArea = bottomArea;
    Rectangle<int> filterEgArea = bottomBottomArea.removeFromLeft(bottomKnobWidth * 4);
    bottomBottomArea.removeFromLeft(margin);
    m_filterEgAtkSlider.setBounds(filterEgArea.removeFromLeft(bottomKnobWidth));
    m_filterEgDecSlider.setBounds(filterEgArea.removeFromLeft(bottomKnobWidth));
    m_filterEgSusSlider.setBounds(filterEgArea.removeFromLeft(bottomKnobWidth));
    m_filterEgRelSlider.setBounds(filterEgArea.removeFromLeft(bottomKnobWidth));

    Rectangle<int> modEgArea = bottomBottomArea;
    m_modEgAtkSlider.setBounds(modEgArea.removeFromLeft(bottomKnobWidth));
    m_modEgDecSlider.setBounds(modEgArea.removeFromLeft(bottomKnobWidth));
    m_modEgSusSlider.setBounds(modEgArea.removeFromLeft(bottomKnobWidth));
    m_modEgRelSlider.setBounds(modEgArea.removeFromLeft(bottomKnobWidth));
}
