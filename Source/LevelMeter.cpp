#include "LevelMeter.h"

LevelMeter::LevelMeter(std::atomic<float>& measurementL_, std::atomic<float>& measurementR_)
	: measurementL(measurementL_), measurementR(measurementR_)
{
	setOpaque(true);
	startTimerHz(1);
}

LevelMeter::~LevelMeter()
{
}

void LevelMeter::paint(juce::Graphics&)
{
}

void LevelMeter::resized()
{
}

void LevelMeter::timerCallback()
{
}
