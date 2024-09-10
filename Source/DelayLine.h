#pragma once

#include <memory>

class DelayLine
{
public:
	void setMaximumDelayInSamples(int maxLengthinSamples);
	void reset() noexcept;

	void write(float input) noexcept;
	float read(float delayInSamples) const noexcept;

	int getBufferLength() const noexcept
	{
		return bufferLength;
	}

private:
	float calculateSimpleRead(float delayInSamples) const noexcept;
	float calculateLinearInterpolationRead(float delayInSamples) const noexcept;
	float calculateHermiteInterpolationRead(float DelayInSamples) const noexcept;

	std::unique_ptr<float[]> buffer;
	int bufferLength = 0;
	int writeIndex = 0;
};
