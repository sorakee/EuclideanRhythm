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
    addAndMakeVisible(knobs);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 400);
    setResizable(true, true);
    const juce::Displays::Display* screen = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay();
    if (screen != nullptr)
    {
        setResizeLimits(700, 350,
            (screen->userArea).getWidth(), 
            (screen->userArea).getHeight());
    }
    else
    {
        setResizeLimits(700, 350, 1200, 600);
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
    g.setColour(juce::Colours::black);
    g.fillRect(visualizerArea);

    // g.setColour (juce::Colours::white);
    // g.setFont (15.0f);
    // g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void EuclideanRhythmAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto area = getLocalBounds();

    // Reserve right half of the main area for knobs and buttons
    knobs.setBounds(area.removeFromRight(area.getWidth() * 0.5));
}