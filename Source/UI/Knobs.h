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

	juce::ShapeButton* getToggle(int compNum);
	std::vector<juce::Slider*> getSliders(int compNum);
	
private:

	using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
	using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

	// Red Knobs
	RedSlider stepSlider1, beatSlider1, offsetSlider1;
	RedSlider frequencySlider1, volumeSlider1;
	// Green Knobs
	GreenSlider stepSlider2, beatSlider2, offsetSlider2; 
	GreenSlider frequencySlider2, volumeSlider2;
	// Blue Knobs
	BlueSlider stepSlider3, beatSlider3, offsetSlider3; 
	BlueSlider frequencySlider3, volumeSlider3;
	// Yellow Knows
	YellowSlider stepSlider4, beatSlider4, offsetSlider4; 
	YellowSlider frequencySlider4, volumeSlider4;

	Toggle toggleRed, toggleGreen, toggleBlue, toggleYellow;

	juce::Label stepLabel1, stepLabel2, stepLabel3, stepLabel4;
	juce::Label beatLabel1, beatLabel2, beatLabel3, beatLabel4;
	juce::Label offsetLabel1, offsetLabel2, offsetLabel3, offsetLabel4;

	std::unique_ptr<SliderAttachment> stepAttach1, beatAttach1, offsetAttach1;
	std::unique_ptr<SliderAttachment> stepAttach2, beatAttach2, offsetAttach2;
	std::unique_ptr<SliderAttachment> stepAttach3, beatAttach3, offsetAttach3;
	std::unique_ptr<SliderAttachment> stepAttach4, beatAttach4, offsetAttach4;
	std::unique_ptr<SliderAttachment> frequencyAttach1, frequencyAttach2;
	std::unique_ptr<SliderAttachment> frequencyAttach3, frequencyAttach4;
	std::unique_ptr<SliderAttachment> volumeAttach1, volumeAttach2;
	std::unique_ptr<SliderAttachment> volumeAttach3, volumeAttach4;
	std::unique_ptr<ButtonAttachment> toggleAttach1, toggleAttach2, toggleAttach3, toggleAttach4;

	std::vector<juce::Component*> getComponents(int compNum);
	
	void initComponents();
	void initLimit();
	void attachSliders (juce::AudioProcessorValueTreeState& apvts, int compNum);
	void toggleSliders();

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Knobs)
};