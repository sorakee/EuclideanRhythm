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
    const int noOfComps = 4;

    // Initialise rotary slider components
    for (int i = 0; i < noOfComps; i++)
    {
        for (auto* component : getComponents(i))
        {
            addAndMakeVisible(component);
        }
    } 

    

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 400);
    setResizable(true, true);
    getConstrainer()->setFixedAspectRatio(2.0);
}

EuclideanRhythmAudioProcessorEditor::~EuclideanRhythmAudioProcessorEditor()
{
}

//==============================================================================
void EuclideanRhythmAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // g.setColour (juce::Colours::white);
    // g.setFont (15.0f);
    // g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void EuclideanRhythmAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto area = getLocalBounds();
    // Reserve right half of the main area for knobs
    auto knobsArea = area.removeFromRight(area.getWidth() * 0.5);
    // Reserve bottom area of knobs area for playback buttons
    auto playbackButtonArea = knobsArea.removeFromBottom(knobsArea.getHeight() * 0.2);
    // Reserve remaining knobs area for upper area knobs
    auto knobsUpperArea = knobsArea.removeFromTop(knobsArea.getHeight() * 0.5);
    auto knobsUpperLeftArea = knobsUpperArea.removeFromLeft(knobsUpperArea.getWidth() * 0.5);
    auto knobsBottomLeftArea = knobsArea.removeFromLeft(knobsArea.getWidth() * 0.5);

    // Top-left Knobs
    stepSlider1.setBounds(knobsUpperLeftArea.removeFromLeft(
        knobsUpperLeftArea.getWidth() * 0.33));
    beatSlider1.setBounds(knobsUpperLeftArea.removeFromLeft(
        knobsUpperLeftArea.getWidth() * 0.5));
    offsetSlider1.setBounds(knobsUpperLeftArea);

    // Top-right Knobs
    stepSlider2.setBounds(knobsUpperArea.removeFromLeft(
        knobsUpperArea.getWidth() * 0.33));
    beatSlider2.setBounds(knobsUpperArea.removeFromLeft(
        knobsUpperArea.getWidth() * 0.5));
    offsetSlider2.setBounds(knobsUpperArea);

    // Bottom-left Knobs
    stepSlider3.setBounds(knobsBottomLeftArea.removeFromLeft(
        knobsBottomLeftArea.getWidth() * 0.33));
    beatSlider3.setBounds(knobsBottomLeftArea.removeFromLeft(
        knobsBottomLeftArea.getWidth() * 0.5));
    offsetSlider3.setBounds(knobsBottomLeftArea);

    // Bottom-right Knobs
    stepSlider4.setBounds(knobsArea.removeFromLeft(
        knobsArea.getWidth() * 0.33));
    beatSlider4.setBounds(knobsArea.removeFromLeft(
        knobsArea.getWidth() * 0.5));
    offsetSlider4.setBounds(knobsArea);
}

std::vector<juce::Component*> EuclideanRhythmAudioProcessorEditor::getComponents(int compNum)
{
    std::vector<juce::Component*> comps;

    switch (compNum)
    {
    case 0:
        comps = {
            &stepSlider1,
            &beatSlider1,
            &offsetSlider1,
        };
        break;
    case 1:
        comps = {
            &stepSlider2,
            &beatSlider2,
            &offsetSlider2,
        };
        break;
    case 2:
        comps = {
            &stepSlider3,
            &beatSlider3,
            &offsetSlider3,
        };
        break;
    case 3:
        comps = {
            &stepSlider4,
            &beatSlider4,
            &offsetSlider4,
        };
        break;
    }
    
    return comps;
}