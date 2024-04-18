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
    reset.setColour(juce::TextButton::buttonColourId,
        juce::Colours::black);
    reset.setButtonText("Reset");

    darkMode.setColour(juce::TextButton::buttonColourId,
        juce::Colours::whitesmoke);
    darkMode.setColour(juce::TextButton::textColourOffId,
        juce::Colours::black);
    darkMode.setButtonText("Dark Mode");
    darkMode.setToggleable(true);
    darkMode.setClickingTogglesState(true);

    darkMode.onClick = [this]
        {
            if (darkMode.getToggleState())
            {
                knobs.setDark(true);
                knobs.repaint();
                darkMode.setColour(darkMode.buttonOnColourId, juce::Colours::darkgrey);
                darkMode.setColour(darkMode.textColourOnId, juce::Colours::white);
                darkMode.setButtonText("Light Mode");
            }
            else
            {
                knobs.setDark(false);
                knobs.repaint();
                darkMode.setButtonText("Dark Mode");
            }
        };

    addAndMakeVisible(reset);
    addAndMakeVisible(darkMode);
    addAndMakeVisible(visualizer);
    addAndMakeVisible(knobs);

    // Assign event handling functions for each knob
    eventHandler(p);

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

    // Reserve bottom control area for misc buttons
    reset.setBounds(controlArea.removeFromLeft(controlArea.getWidth() * 0.5));
    darkMode.setBounds(controlArea);
}

void EuclideanRhythmAudioProcessorEditor::eventHandler(EuclideanRhythmAudioProcessor& p)
{
    // TODO : Move all lambda functions in all UI classes here?

    /*
    * slider[0] - Steps Slider
    * slider[1] - Beats Slider
    * slider[2] - Offset Slider
    * slider[3] - Frequency Slider
    * slider[4] - Volume Slider
    * slider[5] - Speed Slider
    */

    // TODO: Change this number to 4 when other slider groups are attached to processor
    const int numComps = 4;

    for (int i = 0; i < numComps; ++i)
    {
        // i refers to group of knobs
        // i = 0 -> red group
        // i = 1 -> green group
        // i = 2 -> blue group
        // i = 3 -> yellow group

        // Retrieve slider from Knobs class
        std::vector<juce::Slider*> slider = knobs.getSliders(i);
        slider[0]->onDragEnd = [this, slider, &p, i]
            {
                p.reset(i);

                if (slider[1]->getValue() > slider[0]->getValue())
                {
                    slider[1]->setValue(slider[0]->getValue());
                }

                if (slider[2]->getValue() > slider[0]->getValue())
                {
                    slider[2]->setValue(slider[0]->getValue());
                }

                slider[1]->setRange(0, slider[0]->getValue(), 1);
                slider[2]->setRange(0, slider[0]->getValue(), 1);

                slider[1]->repaint();
                slider[2]->repaint();

                visualizer.setNumEllipses(static_cast<int>(slider[0]->getValue()),
                    static_cast<int>(slider[1]->getValue()),
                    i, slider[2]->getValue());
                visualizer.getNeedle(i)->setSteps(slider[0]->getValue());
                visualizer.getNeedle(i)->startNeedle(p.getInterval(i));
            };

        slider[1]->onDragEnd = [this, slider, &p, i]
            {
                p.reset(i);

                visualizer.setNumEllipses(static_cast<int>(slider[0]->getValue()),
                    static_cast<int>(slider[1]->getValue()),
                    i, slider[2]->getValue());
                visualizer.getNeedle(i)->startNeedle(p.getInterval(i));
            };

        slider[2]->onDragEnd = [this, slider, &p, i]
            {
                p.reset(i);

                visualizer.setNumEllipses(static_cast<int>(slider[0]->getValue()),
                    static_cast<int>(slider[1]->getValue()),
                    i, slider[2]->getValue());
                visualizer.getNeedle(i)->startNeedle(p.getInterval(i));
            };

        slider[5]->onDragEnd = [this, slider, &p, i]
            {
                p.reset(i);
                p.setInit(i, true);

                visualizer.getNeedle(i)->setAngle(-juce::MathConstants<float>::halfPi);
                visualizer.getNeedle(i)->startNeedle(p.getInterval(i));
            };

        // Retrieve toggle from Knobs class
        juce::ShapeButton* button = knobs.getToggle(i);
        button->onClick = [this, button, slider, &p, i]
            {
                if (button->getToggleState())
                {
                    visualizer.toggleStatus(i, true);
                    visualizer.getNeedle(i)->setSteps(slider[0]->getValue());
                    visualizer.getNeedle(i)->startNeedle(p.getInterval(i));
                }
                else
                {
                    visualizer.toggleStatus(i, false);
                    visualizer.getNeedle(i)->stopNeedle();
                }
            };
    }

    reset.onClick = [this, &p]
        {
            for (int i = 0; i < 4; ++i)
            {
                if (!knobs.getToggle(i)->getToggleState()) 
                { 
                    continue;
                }

                p.reset(i);
                visualizer.getNeedle(i)->startNeedle(p.getInterval(i));
                visualizer.getNeedle(i)->resetNeedle();
            }
        };

    // ALTERNATE METHOD IN CASE ABOVE METHOD DOESN'T WORK
    /*
    std::vector<juce::Slider*> slider;
    juce::ShapeButton* button;

    std::vector<std::vector<juce::Slider*>> sliderGroup;
    std::vector<juce::ShapeButton*> toggleGroup;
    sliderGroup.resize(numComps);
    toggleGroup.resize(numComps);

    for (int i = 0; i < numComps; ++i)
    {
        // Retrieve slider from Knobs class
        slider = knobs.getSliders(i);
        sliderGroup[i] = slider;
        sliderGroup[i][0]->onDragEnd = [this, sliderGroup, &p, i]
            {
                p.reset();

                if (sliderGroup[i][1]->getValue() > sliderGroup[i][0]->getValue())
                {
                    sliderGroup[i][1]->setValue(sliderGroup[i][0]->getValue());
                }

                if (sliderGroup[i][2]->getValue() > sliderGroup[i][0]->getValue())
                {
                    sliderGroup[i][2]->setValue(sliderGroup[i][0]->getValue());
                }

                auto beatRange = sliderGroup[i][1]->getRange();
                auto sliderRange = sliderGroup[i][2]->getRange();
                sliderGroup[i][1]->setRange(0, sliderGroup[i][0]->getValue(), 1);
                sliderGroup[i][2]->setRange(0, sliderGroup[i][0]->getValue(), 1);

                sliderGroup[i][1]->repaint();
                sliderGroup[i][2]->repaint();

                visualizer.setNumEllipses(static_cast<int>(sliderGroup[i][0]->getValue()),
                    static_cast<int>(sliderGroup[i][1]->getValue()),
                    0);
                visualizer.getNeedle()->setSteps(sliderGroup[i][0]->getValue());
                visualizer.getNeedle()->startNeedle(p.getInterval());
            };

        sliderGroup[i][1]->onDragEnd = [this, sliderGroup, &p, i]
            {
                p.reset();

                visualizer.setNumEllipses(static_cast<int>(sliderGroup[i][0]->getValue()),
                    static_cast<int>(sliderGroup[i][1]->getValue()),
                    0);
                visualizer.getNeedle()->startNeedle(p.getInterval());
            };

        // Retrieve toggle from Knobs class
        button = knobs.getToggle(i);
        toggleGroup[i] = button;
        toggleGroup[i]->onClick = [this, toggleGroup, sliderGroup, &p, i]
            {
                if (toggleGroup[i]->getToggleState())
                {
                    visualizer.toggleStatus(i, true);
                    visualizer.getNeedle()->setSteps(sliderGroup[i][0]->getValue());
                    visualizer.getNeedle()->startNeedle(p.getInterval());
                }
                else
                {
                    visualizer.toggleStatus(i, false);
                    visualizer.getNeedle()->stopNeedle();
                }
            };
    }
    */
}