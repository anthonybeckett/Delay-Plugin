#pragma once

#include <JuceHeader.h>

const juce::ParameterID gainParamId{ "gain", 1 };
const juce::ParameterID delayTimeParamId{ "delayTime", 1 };
const juce::ParameterID mixParamId { "mix", 1 };
const juce::ParameterID feedbackParamId{ "feedback", 1 };
const juce::ParameterID stereoParamId{ "stereo", 1 };
const juce::ParameterID lowCutParamId { "lowCut", 1 };
const juce::ParameterID highCutParamId{ "highCut", 1 };
const juce::ParameterID tempoSyncParamId{ "tempoSync", 1 };
const juce::ParameterID delayNoteParamId{ "delayNote", 1 };

class Parameters 
{
public:
	Parameters(juce::AudioProcessorValueTreeState& apvts);

	static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

	void update() noexcept;

	void prepareToPlay(double sampleRate) noexcept;
	void reset() noexcept;
	void smoothen() noexcept;

	float gain = 0.0f;
	float delayTime = 0.0f;
	float mix = 1.0f;
	float feedback = 0.0f;
	float panL = 0.0f;
	float panR = 1.0f;
	float lowCut = 20.0f;
	float highCut = 20000.0f;
	int delayNote = 0;
	bool tempoSync = false;

	static constexpr float minDelayTime = 5.0f;
	static constexpr float maxDelayTime = 5000.0f;

	juce::AudioParameterBool* tempoSyncParam;

private:
	juce::AudioParameterFloat* gainParam;
	juce::AudioParameterFloat* delayTimeParam;

	juce::LinearSmoothedValue<float> gainSmoother;

	float targetDelayTime = 0.0f;
	float coeff = 0.0f;

	juce::AudioParameterFloat* mixParam;
	juce::LinearSmoothedValue<float> mixSmoother;

	juce::AudioParameterFloat* feedbackParam;
	juce::LinearSmoothedValue<float> feedbackSmoother;

	juce::AudioParameterFloat* stereoParam;
	juce::LinearSmoothedValue<float> stereoSmoother;

	juce::AudioParameterFloat* lowCutParam;
	juce::LinearSmoothedValue<float> lowCutSmoother;

	juce::AudioParameterFloat* highCutParam;
	juce::LinearSmoothedValue<float> highCutSmoother;
	
	juce::AudioParameterChoice* delayNoteParam;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Parameters)
};
