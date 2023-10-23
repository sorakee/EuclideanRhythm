/*
  ==============================================================================

	This file contains the code for the main components.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "RedSlider.h"
#include "GreenSlider.h"
#include "BlueSlider.h"
#include "YellowSlider.h"

class Knobs : public juce::Component
{
public:
	Knobs(juce::AudioProcessorValueTreeState& apvts);
	~Knobs() override;

	void paint(juce::Graphics&) override;
	void resized() override;
private:

	using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

	// Red Knobs
	RedSlider stepSlider1, beatSlider1, offsetSlider1;
	// Green Knobs
	GreenSlider stepSlider2, beatSlider2, offsetSlider2;
	// Blue Knobs
	BlueSlider stepSlider3, beatSlider3, offsetSlider3;
	// Yellow Knows
	YellowSlider stepSlider4, beatSlider4, offsetSlider4;

	std::unique_ptr<SliderAttachment> stepAttach1, beatAttach1, offsetAttach1;
	std::unique_ptr<SliderAttachment> stepAttach2, beatAttach2, offsetAttach2;
	std::unique_ptr<SliderAttachment> stepAttach3, beatAttach3, offsetAttach3;
	std::unique_ptr<SliderAttachment> stepAttach4, beatAttach4, offsetAttach4;

	std::vector<juce::Slider*> getSliders(int compNum);
	void attachSliders (juce::AudioProcessorValueTreeState& apvts, int compNum);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Knobs)
};