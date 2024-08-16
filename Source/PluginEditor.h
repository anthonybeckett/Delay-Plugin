#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Parameters.h"
#include "RotaryKnob.h"
#include "LookAndFeel.h"

class DelayAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DelayAudioProcessorEditor (DelayAudioProcessor&);
    ~DelayAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    DelayAudioProcessor& audioProcessor;

    RotaryKnob gainKnob{ "Gain", audioProcessor.apvts, gainParamId, true };
    RotaryKnob mixKnob{ "Mix", audioProcessor.apvts, mixParamId };
    RotaryKnob delayTimeKnob{ "Time", audioProcessor.apvts, delayTimeParamId };
    RotaryKnob feedbackKnob{ "Feedback", audioProcessor.apvts, feedbackParamId, true };
    RotaryKnob stereoKnob{ "Stereo", audioProcessor.apvts, stereoParamId, true };
    RotaryKnob lowCutKnob{ "Low Cut", audioProcessor.apvts, lowCutParamId };
    RotaryKnob highCutKnob{ "High Cut", audioProcessor.apvts, highCutParamId };

    juce::GroupComponent delayGroup;
    juce::GroupComponent feedbackGroup;
    juce::GroupComponent outputGroup;

    MainLookAndFeel mainLF;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayAudioProcessorEditor)
};
