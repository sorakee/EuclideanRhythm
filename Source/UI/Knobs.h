/*
  ==============================================================================

	This file contains the code for Knob components.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "RotarySlider.h"

class Knobs : public juce::Component
{
public:
	Knobs(juce::AudioProcessorValueTreeState& apvts);
	~Knobs() override;

	void paint(juce::Graphics&) override;
	void resized() override;
private:

	using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

	RotarySlider stepSlider1, beatSlider1, offsetSlider1;
	RotarySlider stepSlider2, beatSlider2, offsetSlider2;
	RotarySlider stepSlider3, beatSlider3, offsetSlider3;
	RotarySlider stepSlider4, beatSlider4, offsetSlider4;

	std::unique_ptr<SliderAttachment> stepAttach1, beatAttach1, offsetAttach1;
	std::unique_ptr<SliderAttachment> stepAttach2, beatAttach2, offsetAttach2;
	std::unique_ptr<SliderAttachment> stepAttach3, beatAttach3, offsetAttach3;
	std::unique_ptr<SliderAttachment> stepAttach4, beatAttach4, offsetAttach4;

	std::vector<juce::Slider*> getSliders(int compNum);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Knobs)
};