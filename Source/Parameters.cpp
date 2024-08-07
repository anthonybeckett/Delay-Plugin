#include "Parameters.h"
#include "DSP.h"

template<typename T>
static void castParameter(juce::AudioProcessorValueTreeState& apvts, const juce::ParameterID& id, T& destination)
{
    destination = dynamic_cast<T>(apvts.getParameter(id.getParamID()));
    jassert(destination);
}

static juce::String stringFromMilliseconds(float value, int)
{
    if (value < 10.0f) {
        return juce::String(value, 2) + " ms";
    }
    else if (value < 100.0f) {
        return juce::String(value, 1) + " ms";
    }
    else if (value < 1000.0f) {
        return juce::String(int(value)) + " ms";
    }
    else {
        return juce::String(value * 0.001f, 2) + " s";
    }
}

static float millisecondsFromString(const juce::String& text) 
{
    float value = text.getFloatValue();

    if (!text.endsWithIgnoreCase("ms") && (text.endsWithIgnoreCase("s") || value < Parameters::minDelayTime)) {
        return value * 1000.0f;
    }

    return value;
}

static juce::String stringFromPercent(float value, int)
{
    return juce::String(int(value)) + " %";
}

static juce::String stringFromDecibels(float value, int) 
{
    return juce::String(value, 1) + " dB";
}

Parameters::Parameters(juce::AudioProcessorValueTreeState& apvts)
{
    castParameter(apvts, gainParamId, gainParam);
    castParameter(apvts, delayTimeParamId, delayTimeParam);
    castParameter(apvts, mixParamId, mixParam);
    castParameter(apvts, feedbackParamId, feedbackParam);
    castParameter(apvts, stereoParamId, stereoParam);
}

juce::AudioProcessorValueTreeState::ParameterLayout Parameters::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        gainParamId,
        "Output Gain",
        juce::NormalisableRange<float> {-12.0f, 12.0f},
        0.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromDecibels)
    ));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        delayTimeParamId,
        "Delay Time",
        juce::NormalisableRange<float> {minDelayTime, maxDelayTime, 0.001f, 0.25f},
        100.0f,
        juce::AudioParameterFloatAttributes()
            .withStringFromValueFunction(stringFromMilliseconds)
            .withValueFromStringFunction(millisecondsFromString)
    ));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        mixParamId,
        "Mix",
        juce::NormalisableRange<float>(0.0f, 100.0f, 1.0f),
        100.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromPercent)
    ));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        feedbackParamId,
        "Feedback",
        juce::NormalisableRange<float>(-100.0f, 100.0f, 1.0f),
        0.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromPercent)
    ));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        stereoParamId,
        "Stereo",
        juce::NormalisableRange<float>(-100.0f, 100.0f, 1.0f),
        0.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromPercent)
    ));

    return layout;
}

void Parameters::update() noexcept
{
    float gainInDecibels = gainParam->get();
    float newGain = juce::Decibels::decibelsToGain(gainInDecibels);
    gainSmoother.setTargetValue(newGain);

    targetDelayTime = delayTimeParam->get();
    if (delayTime == 0.0f) {
        delayTime = targetDelayTime;
    }

    mixSmoother.setCurrentAndTargetValue(mixParam->get() * 0.01f);
    feedbackSmoother.setCurrentAndTargetValue(feedbackParam->get() * 0.01f);
    stereoSmoother.setTargetValue(stereoParam->get() * 0.01f);
}

void Parameters::prepareToPlay(double sampleRate) noexcept
{
    double duration = 0.02;
    gainSmoother.reset(sampleRate, duration);

    coeff = 1.0f - std::exp(-1.0f / (0.2f * float(sampleRate)));

    mixSmoother.reset(sampleRate, duration);

    feedbackSmoother.reset(sampleRate, duration);

    stereoSmoother.reset(sampleRate, duration);
}

void Parameters::reset() noexcept
{
    gain = 0.0f;
    gainSmoother.setCurrentAndTargetValue(juce::Decibels::decibelsToGain(gainParam->get()));

    delayTime = 0.0f;

    mix = 1.0f;
    mixSmoother.setCurrentAndTargetValue(mixParam->get() * 0.01f);

    feedback = 0.0f;
    feedbackSmoother.setCurrentAndTargetValue(feedbackParam->get() * 0.01f);

    stereoSmoother.setCurrentAndTargetValue(stereoParam->get() * 0.01f);

    float panL = 0.0f;
    float panR = 1.0f;
}

void Parameters::smoothen() noexcept
{
    gain = gainSmoother.getNextValue();

    delayTime += (targetDelayTime - delayTime) * coeff;

    mix = mixSmoother.getNextValue();

    feedback = feedbackSmoother.getNextValue();

    panningEqualPower()
}
