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
    : AudioProcessorEditor (&p), 
    audioProcessor (p), 
    apvts (apvts), 
    knobs (apvts),
    visualizer (apvts)
{
    // Placeholder
    placeholder.setColour(juce::TextButton::buttonColourId,
        juce::Colours::cornflowerblue);
    placeholder.setButtonText("PLACEHOLDER");

    addAndMakeVisible(placeholder);
    addAndMakeVisible(visualizer);
    addAndMakeVisible(knobs);

    /*
    * slider1[0] - Steps Slider
    * slider1[1] - Beats Slider
    * slider1[2] - Offset Slider
    */
    std::vector<juce::Slider*> slider1 = knobs.getSliders(0);
    slider1[0]->onDragEnd = [this, slider1]
        {
            visualizer.setNumEllipses(static_cast<int>(slider1[0]->getValue()),
                                      static_cast<int>(slider1[1]->getValue()));
        };

    slider1[1]->onDragEnd = [this, slider1]
        {
            visualizer.setNumEllipses(static_cast<int>(slider1[0]->getValue()),
                static_cast<int>(slider1[1]->getValue()));
        };

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
}

void EuclideanRhythmAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto area = getLocalBounds();

    // Reserve right half of the main area for control area
    auto controlArea = area.removeFromRight(area.getWidth() * 0.5);

    // Reserve left half of the main area for visualizer area
    visualizer.setBounds(area);

    // Reserve upper control area for knobs
    knobs.setBounds(controlArea.removeFromTop(controlArea.getHeight() * 0.8));

    // Reserve bottom control area for playback buttons
    placeholder.setBounds(controlArea);
}