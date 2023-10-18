/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/Knobs.h"

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
    Knobs knobs;
    juce::TextButton placeholder;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EuclideanRhythmAudioProcessorEditor)
};
