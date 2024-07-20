#include <JuceHeader.h>
#include "RotaryKnob.h"
#include "LookAndFeel.h"

RotaryKnob::RotaryKnob(const juce::String& text, juce::AudioProcessorValueTreeState& apvts, const juce::ParameterID& parameterId, bool drawFromMiddle)
    : attachment(apvts, parameterId.getParamID(), slider)
{
    setLookAndFeel(RotaryKnobLookAndFeel::get());

    float pi = juce::MathConstants<float>::pi;

    slider.setRotaryParameters(1.25f * pi, 2.75 * pi, true);
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 16);
    slider.setBounds(0, 0, 70, 86);
    slider.getProperties().set("drawFromMiddle", drawFromMiddle);
    addAndMakeVisible(slider);

    label.setText(text, juce::NotificationType::dontSendNotification);
    label.setJustificationType(juce::Justification::horizontallyCentred);
    label.setBorderSize(juce::BorderSize<int>(0, 0, 2, 0));
    label.attachToComponent(&slider, false);
    addAndMakeVisible(label);

    setSize(70, 110);
}

RotaryKnob::~RotaryKnob()
{
}

void RotaryKnob::resized()
{
    slider.setTopLeftPosition(0, 24);

}
