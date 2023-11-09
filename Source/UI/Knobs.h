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
#include "Toggle.h"

class Knobs : public juce::Component
{
public:
	Knobs(juce::AudioProcessorValueTreeState& apvts);
	~Knobs() override;

	void paint(juce::Graphics&) override;
	void resized() override;

	std::vector<juce::Slider*> getSliders(int compNum);
	std::vector<juce::ShapeButton*> getToggles();
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

	Toggle toggleRed, toggleGreen, toggleBlue, toggleYellow;

	juce::Label stepLabel1, stepLabel2, stepLabel3, stepLabel4;
	juce::Label beatLabel1, beatLabel2, beatLabel3, beatLabel4;
	juce::Label offsetLabel1, offsetLabel2, offsetLabel3, offsetLabel4;

	std::unique_ptr<SliderAttachment> stepAttach1, beatAttach1, offsetAttach1;
	std::unique_ptr<SliderAttachment> stepAttach2, beatAttach2, offsetAttach2;
	std::unique_ptr<SliderAttachment> stepAttach3, beatAttach3, offsetAttach3;
	std::unique_ptr<SliderAttachment> stepAttach4, beatAttach4, offsetAttach4;

	std::vector<juce::Component*> getComponents(int compNum);
	
	void initComponents();
	void attachSliders (juce::AudioProcessorValueTreeState& apvts, int compNum);
	void toggleSliders();
	void changeLimit(juce::AudioProcessorValueTreeState& apvts);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Knobs)
};