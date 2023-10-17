/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

struct RotarySlider : juce::Slider
{
    RotarySlider() : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
        juce::Slider::TextEntryBoxPosition::TextBoxBelow)
    {
    }
};

//==============================================================================
/**
*/
class EuclideanRhythmAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    EuclideanRhythmAudioProcessorEditor (EuclideanRhythmAudioProcessor&, 
        juce::AudioProcessorValueTreeState&);
    ~EuclideanRhythmAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EuclideanRhythmAudioProcessor& audioProcessor;

    juce::AudioProcessorValueTreeState& apvts;

    RotarySlider stepSlider1, beatSlider1, offsetSlider1;
    RotarySlider stepSlider2, beatSlider2, offsetSlider2;
    RotarySlider stepSlider3, beatSlider3, offsetSlider3;
    RotarySlider stepSlider4, beatSlider4, offsetSlider4;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> stepAttach1, beatAttach1, offsetAttach1;
    std::unique_ptr<SliderAttachment> stepAttach2, beatAttach2, offsetAttach2;
    std::unique_ptr<SliderAttachment> stepAttach3, beatAttach3, offsetAttach3;
    std::unique_ptr<SliderAttachment> stepAttach4, beatAttach4, offsetAttach4;

    std::vector<juce::Component*> getComponents(int compNum);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EuclideanRhythmAudioProcessorEditor)
};
