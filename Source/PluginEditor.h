#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Parameters.h"
#include "RotaryKnob.h"
#include "LookAndFeel.h"
#include "LevelMeter.h"

class DelayAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::AudioProcessorParameter::Listener
{
public:
    DelayAudioProcessorEditor (DelayAudioProcessor&);
    ~DelayAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void parameterValueChanged(int, float) override;
    void parameterGestureChanged(int, bool) override {}

    void updateDelayKnobs(bool tempoSyncActive);

    DelayAudioProcessor& audioProcessor;

    RotaryKnob gainKnob{ "Gain", audioProcessor.apvts, gainParamId, true };
    RotaryKnob mixKnob{ "Mix", audioProcessor.apvts, mixParamId };
    RotaryKnob delayTimeKnob{ "Time", audioProcessor.apvts, delayTimeParamId };
    RotaryKnob feedbackKnob{ "Feedback", audioProcessor.apvts, feedbackParamId, true };
    RotaryKnob stereoKnob{ "Stereo", audioProcessor.apvts, stereoParamId, true };
    RotaryKnob lowCutKnob{ "Low Cut", audioProcessor.apvts, lowCutParamId };
    RotaryKnob highCutKnob{ "High Cut", audioProcessor.apvts, highCutParamId };
    RotaryKnob delayNoteKnob{ "Note", audioProcessor.apvts, delayNoteParamId };
    
    juce::TextButton tempoSyncButton;
    juce::AudioProcessorValueTreeState::ButtonAttachment tempoSyncAttachment { audioProcessor.apvts, tempoSyncParamId.getParamID(), tempoSyncButton };

    juce::GroupComponent delayGroup;
    juce::GroupComponent feedbackGroup;
    juce::GroupComponent outputGroup;

    MainLookAndFeel mainLF;

    LevelMeter meter;

    juce::ImageButton bypassButton;

    juce::AudioProcessorValueTreeState::ButtonAttachment bypassAttachment{
        audioProcessor.apvts,
        bypassParamId.getParamID(),
        bypassButton
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayAudioProcessorEditor)
};
