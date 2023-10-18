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
    : AudioProcessorEditor (&p), audioProcessor (p), apvts (apvts), knobs (apvts)
{
    // Placeholder
    placeholder.setColour(juce::TextButton::buttonColourId,
        juce::Colours::cornflowerblue);
    placeholder.setButtonText("PLACEHOLDER");
    addAndMakeVisible(placeholder);

    addAndMakeVisible(knobs);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 400);
    setResizable(true, true);
    const juce::Displays::Display* screen = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay();
    if (screen != nullptr)
    {
        setResizeLimits(800, 400,
            static_cast<int>((screen->userArea).getWidth() * 0.75),
            static_cast<int>((screen->userArea).getHeight() * 0.75));
    }
    else
    {
        setResizeLimits(800, 400, 1200, 600);
    }
    
    getConstrainer()->setFixedAspectRatio(2.0);
}

EuclideanRhythmAudioProcessorEditor::~EuclideanRhythmAudioProcessorEditor()
{
}

//==============================================================================
void EuclideanRhythmAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    auto area = getLocalBounds();
    // Assign the left half of main area a space for the visualizer
    auto visualizerArea = area.removeFromLeft(area.getWidth() * 0.5);
    g.setColour(juce::Colour(0.f, 0.f, 13.f / 255.f, 1.f));
    g.fillRect(visualizerArea);
}

void EuclideanRhythmAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto area = getLocalBounds();

    // Reserve right half of the main area for control Area
    auto controlArea = area.removeFromRight(area.getWidth() * 0.5);

    // Reserve upper control area for knobs
    knobs.setBounds(controlArea.removeFromTop(controlArea.getHeight() * 0.8));

    // Reserve bottom control area for playback buttons
    placeholder.setBounds(controlArea);
}