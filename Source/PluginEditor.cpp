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
    for (int i = 0; i < noOfComps; ++i)
    {
        for (auto* component : getComponents(i))
        {
            addAndMakeVisible(component);
        }
    } 

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    // Make connection between rotary slider and parameter in 'apvts'
    for (int i = 0; i < noOfComps; ++i)
    {
        auto stepsParam = juce::String(std::string("Steps ") + std::to_string(i + 1));
        auto beatsParam = juce::String(std::string("Beats ") + std::to_string(i + 1));
        auto offsetParam = juce::String(std::string("Offset ") + std::to_string(i + 1));

        switch (i + 1)
        {
        case 1:
            stepAttach1 = std::make_unique<SliderAttachment>(apvts, stepsParam, stepSlider1);
            beatAttach1 = std::make_unique<SliderAttachment>(apvts, beatsParam, beatSlider1);
            offsetAttach1 = std::make_unique<SliderAttachment>(apvts, offsetParam, offsetSlider1);
            break;
        case 2:
            stepAttach2 = std::make_unique<SliderAttachment>(apvts, stepsParam, stepSlider2);
            beatAttach2 = std::make_unique<SliderAttachment>(apvts, beatsParam, beatSlider2);
            offsetAttach2 = std::make_unique<SliderAttachment>(apvts, offsetParam, offsetSlider2);
            break;
        case 3:
            stepAttach3 = std::make_unique<SliderAttachment>(apvts, stepsParam, stepSlider3);
            beatAttach3 = std::make_unique<SliderAttachment>(apvts, beatsParam, beatSlider3);
            offsetAttach3 = std::make_unique<SliderAttachment>(apvts, offsetParam, offsetSlider3);
            break;
        case 4:
            stepAttach4 = std::make_unique<SliderAttachment>(apvts, stepsParam, stepSlider4);
            beatAttach4 = std::make_unique<SliderAttachment>(apvts, beatsParam, beatSlider4);
            offsetAttach4 = std::make_unique<SliderAttachment>(apvts, offsetParam, offsetSlider4);
            break;
        }
    } 

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 400);
    setResizable(true, true);
    const juce::Displays::Display* screen = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay();
    if (screen != nullptr)
    {
        setResizeLimits(600, 300,
            (screen->userArea).getWidth(), 
            (screen->userArea).getHeight());
    }
    else
    {
        setResizeLimits(600, 300, 1200, 600);
    }
    
    getConstrainer()->setFixedAspectRatio(2.0);

    // TODO : Adding slider labels
}

EuclideanRhythmAudioProcessorEditor::~EuclideanRhythmAudioProcessorEditor()
{
}

//==============================================================================
void EuclideanRhythmAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

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
    // Reserve right half of the main area for knobs
    auto knobsArea = area.removeFromRight(area.getWidth() * 0.5);
    // Reserve bottom area of knobs area for playback buttons
    auto playbackButtonArea = knobsArea.removeFromBottom(knobsArea.getHeight() * 0.2);
    // Reserve remaining knobs area for upper area knobs
    auto knobsUpperArea = knobsArea.removeFromTop(knobsArea.getHeight() * 0.5);
    // Reserve upper left area for top-left knobs
    auto knobsUpperLeftArea = knobsUpperArea.removeFromLeft(knobsUpperArea.getWidth() * 0.5);
    // Reserve bottom left area for bottom-left knobs
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

    switch (compNum + 1)
    {
    case 1:
        comps = {
            &stepSlider1,
            &beatSlider1,
            &offsetSlider1,
        };
        break;
    case 2:
        comps = {
            &stepSlider2,
            &beatSlider2,
            &offsetSlider2,
        };
        break;
    case 3:
        comps = {
            &stepSlider3,
            &beatSlider3,
            &offsetSlider3,
        };
        break;
    case 4:
        comps = {
            &stepSlider4,
            &beatSlider4,
            &offsetSlider4,
        };
        break;
    }
    
    return comps;
}