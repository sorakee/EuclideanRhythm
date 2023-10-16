/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EuclideanRhythmAudioProcessorEditor::EuclideanRhythmAudioProcessorEditor (EuclideanRhythmAudioProcessor& p, 
    juce::AudioProcessorValueTreeState& apvts)
    : AudioProcessorEditor (&p), audioProcessor (p), apvts (apvts)
{
    for (auto* component : getComponents())
    {
        addAndMakeVisible(component);
    }

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 400);
}

EuclideanRhythmAudioProcessorEditor::~EuclideanRhythmAudioProcessorEditor()
{
}

//==============================================================================
void EuclideanRhythmAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void EuclideanRhythmAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    // TODO: Add slider components to the GUI

}

std::vector<juce::Component*> EuclideanRhythmAudioProcessorEditor::getComponents()
{
    return
    {
        &stepSlider,
        &beatSlider,
        &offsetSlider
    };
}