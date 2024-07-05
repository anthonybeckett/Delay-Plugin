#pragma once

#include <JuceHeader.h>

const juce::ParameterID gainParamId{ "gain", 1 };
const juce::ParameterID delayTimeParamId{"delayTime", 1};

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

	static constexpr float minDelayTime = 5.0f;
	static constexpr float maxDelayTime = 5000.0f;

private:
	juce::AudioParameterFloat* gainParam;
	juce::AudioParameterFloat* delayTimeParam;

	juce::LinearSmoothedValue<float> gainSmoother;
};
