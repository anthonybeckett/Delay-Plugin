#pragma once

#include <JuceHeader.h>

class LevelMeter : public juce::Component, private juce::Timer
{
public:
	LevelMeter(std::atomic<float>& measurementL_, std::atomic<float>& measurementR_);
	~LevelMeter();

	void paint(juce::Graphics&) override;
	void resized() override;

private:
	void timerCallback() override;
	void drawLevel(juce::Graphics& g, float level, int x, int width);

	std::atomic<float>& measurementL;
	std::atomic<float>& measurementR;

	static constexpr float maxDb = 6.0f;
	static constexpr float minDb = -60.0f;
	static constexpr float stepDb = 6.0f;

	float maxPos = 0.0f;
	float minPos = 0.0f;

	static constexpr float clampDb = -120.0f;
	static constexpr float clampLevel = 0.000001f;

	float dbLevelL = clampDb;
	float dbLevelR = clampDb;

	int positionForLevel(float dbLevel) const noexcept
	{
		return int(std::round(juce::jmap(dbLevel, maxDb, minDb, maxPos, minPos)));
	}

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LevelMeter)
};
