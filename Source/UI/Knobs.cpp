/*
  ==============================================================================

    This file contains the code for the main components.
    Components : Rotary sliders, toggle button, 

  ==============================================================================
*/

#include "Knobs.h"

Knobs::Knobs(juce::AudioProcessorValueTreeState& apvts)
{
    // Initialise components
    // Sliders are disabled by default
    initComponents();

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    // Make connection between rotary slider and parameter in 'apvts'
    attachSliders(apvts, 4);
    
    // Toggle knob groups upon toggle button's state change
    toggleSliders();

    // Ensure beat and offset values does not exceed step value
    changeLimit(apvts);
}

Knobs::~Knobs()
{
}

void Knobs::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightgrey);
    auto area = getLocalBounds();
    // Reserve remaining knobs area for upper area knobs
    auto knobsUpperArea = area.removeFromTop(area.getHeight() * 0.5);

    // Dark Black-ish colour
    g.setColour(juce::Colour(0.f, 0.f, 13.f / 255.f, 1.f));

    // Top Left Border
    auto knobsUpperLeftBorder = knobsUpperArea
        .removeFromLeft(knobsUpperArea.getWidth() * 0.5);
    // Bottom Left Border
    auto knobsBottomLeftBorder = area
        .removeFromLeft(area.getWidth() * 0.5);

    // Draw borders
    g.drawRect(knobsUpperLeftBorder, 2.5f);
    g.drawRect(knobsUpperArea, 2.5f);
    g.drawRect(knobsBottomLeftBorder, 2.5f);
    g.drawRect(area, 2.5f);

}

void Knobs::resized()
{
    auto area = getLocalBounds();
    // Reserve remaining knobs area for upper area knobs
    auto knobsUpperArea = area.removeFromTop(area.getHeight() * 0.5);
    // Reserve upper left area for top-left knobs
    auto knobsUpperLeftArea = knobsUpperArea
        .removeFromLeft(knobsUpperArea.getWidth() * 0.5);
    // Reserve bottom left area for bottom-left knobs
    auto knobsBottomLeftArea = area
        .removeFromLeft(area.getWidth() * 0.5);

    // Top-Left Button
    auto btnUpperLeftArea = knobsUpperLeftArea
        .removeFromBottom(knobsUpperLeftArea.getWidth() * 0.2);
    // Top-Left Toggle
    auto toggleUpperLeftArea = knobsUpperLeftArea
        .removeFromTop(knobsUpperLeftArea.getWidth() * 0.1);
    toggleRed.setBounds(toggleUpperLeftArea.removeFromLeft(
        toggleUpperLeftArea.getWidth() * 0.125));

    // Top-left Knobs
    stepSlider1.setBounds(knobsUpperLeftArea.removeFromLeft(
        knobsUpperLeftArea.getWidth() * 0.33));
    beatSlider1.setBounds(knobsUpperLeftArea.removeFromLeft(
        knobsUpperLeftArea.getWidth() * 0.5));
    offsetSlider1.setBounds(knobsUpperLeftArea);
    stepLabel1.setBounds(stepSlider1.getBounds().expanded(-5.0, -2.5));
    beatLabel1.setBounds(beatSlider1.getBounds().expanded(-5.0, -2.5));
    offsetLabel1 .setBounds(offsetSlider1.getBounds().expanded(-5.0, -2.5));
    auto font = stepLabel1.getFont();
    font.setHeight(stepSlider1.proportionOfWidth(0.275f));
    font.setBold(true);
    font.setTypefaceName("Lato");
    stepLabel1.setFont(font);
    beatLabel1.setFont(font);
    offsetLabel1.setFont(font);

    /* for (auto style : font.findAllTypefaceNames())
    {
        juce::Logger::writeToLog(style);
    } */

    // Top-right Button
    auto btnUpperRightArea = knobsUpperArea
        .removeFromBottom(knobsUpperArea.getWidth() * 0.2);
    // Top-right Toggle
    auto toggleUpperRightArea = knobsUpperArea
        .removeFromTop(knobsUpperArea.getWidth() * 0.1);
    toggleGreen.setBounds(toggleUpperRightArea.removeFromLeft(
        toggleUpperRightArea.getWidth() * 0.125));

    // Top-right Knobs
    stepSlider2.setBounds(knobsUpperArea.removeFromLeft(
        knobsUpperArea.getWidth() * 0.33));
    beatSlider2.setBounds(knobsUpperArea.removeFromLeft(
        knobsUpperArea.getWidth() * 0.5));
    offsetSlider2.setBounds(knobsUpperArea);
    stepLabel2.setBounds(stepSlider2.getBounds().expanded(-5.0, -2.5));
    beatLabel2.setBounds(beatSlider2.getBounds().expanded(-5.0, -2.5));
    offsetLabel2.setBounds(offsetSlider2.getBounds().expanded(-5.0, -2.5));
    stepLabel2.setFont(font);
    beatLabel2.setFont(font);
    offsetLabel2.setFont(font);

    // Bottom-left Button
    auto btnBottomLeftArea = knobsBottomLeftArea
        .removeFromBottom(knobsBottomLeftArea.getWidth() * 0.2);
    // Bottom-left Toggle
    auto toggleBottomLeftArea = knobsBottomLeftArea
        .removeFromTop(knobsBottomLeftArea.getWidth() * 0.1);
    toggleBlue.setBounds(toggleBottomLeftArea.removeFromLeft(
        toggleBottomLeftArea.getWidth() * 0.125));

    // Bottom-left Knobs
    stepSlider3.setBounds(knobsBottomLeftArea.removeFromLeft(
        knobsBottomLeftArea.getWidth() * 0.33));
    beatSlider3.setBounds(knobsBottomLeftArea.removeFromLeft(
        knobsBottomLeftArea.getWidth() * 0.5));
    offsetSlider3.setBounds(knobsBottomLeftArea);
    stepLabel3.setBounds(stepSlider3.getBounds().expanded(-5.0, -2.5));
    beatLabel3.setBounds(beatSlider3.getBounds().expanded(-5.0, -2.5));
    offsetLabel3.setBounds(offsetSlider3.getBounds().expanded(-5.0, -2.5));
    stepLabel3.setFont(font);
    beatLabel3.setFont(font);
    offsetLabel3.setFont(font);

    // Bottom-right Button
    auto btnBottomRightArea = area
        .removeFromBottom(area.getWidth() * 0.2);
    // Bottom-right Toggle
    auto toggleBottomRightArea = area
        .removeFromTop(area.getWidth() * 0.1);
    toggleYellow.setBounds(toggleBottomRightArea.removeFromLeft(
        toggleBottomRightArea.getWidth() * 0.125));

    // Bottom-right Knobs
    stepSlider4.setBounds(area.removeFromLeft(
        area.getWidth() * 0.33));
    beatSlider4.setBounds(area.removeFromLeft(
        area.getWidth() * 0.5));
    offsetSlider4.setBounds(area);
    stepLabel4.setBounds(stepSlider4.getBounds().expanded(-5.0, -2.5));
    beatLabel4.setBounds(beatSlider4.getBounds().expanded(-5.0, -2.5));
    offsetLabel4.setBounds(offsetSlider4.getBounds().expanded(-5.0, -2.5));
    stepLabel4.setFont(font);
    beatLabel4.setFont(font);
    offsetLabel4.setFont(font);
}

std::vector<juce::Component*> Knobs::getComponents(int compNum)
{
    std::vector<juce::Component*> comps;

    switch (compNum + 1)
    {
    case 1:
        comps = {
            &toggleRed,
            &stepLabel1,
            &stepSlider1,
            &beatLabel1,
            &beatSlider1,
            &offsetLabel1,
            &offsetSlider1,
        };
        break;
    case 2:
        comps = {
            &toggleGreen,
            &stepLabel2,
            &stepSlider2,
            &beatLabel2,
            &beatSlider2,
            &offsetLabel2,
            &offsetSlider2,
        };
        break;
    case 3:
        comps = {
            &toggleBlue,
            &stepLabel3,
            &stepSlider3,
            &beatLabel3,
            &beatSlider3,
            &offsetLabel3,
            &offsetSlider3,
        };
        break;
    case 4:
        comps = {
            &toggleYellow,
            &stepLabel4,
            &stepSlider4,
            &beatLabel4,
            &beatSlider4,
            &offsetLabel4,
            &offsetSlider4,
        };
        break;
    }

    return comps;
}

std::vector<juce::Slider*> Knobs::getSliders(int compNum)
{
    std::vector<juce::Slider*> comps;

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

std::vector<juce::ShapeButton*> Knobs::getToggles()
{
    return {
        &toggleRed,
        &toggleGreen,
        &toggleBlue,
        &toggleYellow
    };
}

void Knobs::initComponents()
{
    const int noOfComps = 4;

    // Initialise components
    for (int i = 0; i < noOfComps; ++i)
    {
        for (auto* component : getComponents(i))
        {
            addAndMakeVisible(component);
        }
    }
}

void Knobs::attachSliders(juce::AudioProcessorValueTreeState& apvts, int compNum)
{
    for (int i = 0; i < compNum; ++i)
    {
        auto stepsParam = juce::String(std::string("Steps ") + std::to_string(i + 1));
        auto beatsParam = juce::String(std::string("Beats ") + std::to_string(i + 1));
        auto offsetParam = juce::String(std::string("Offset ") + std::to_string(i + 1));

        switch (i + 1)
        {
        case 1:
            stepLabel1.attachToComponent(&stepSlider1, false);
            stepLabel1.setText("Steps", juce::dontSendNotification);
            stepLabel1.setJustificationType(juce::Justification::centredTop);
            stepLabel1.setColour(juce::Label::textColourId, juce::Colours::black);
            stepAttach1 = std::make_unique<SliderAttachment>(apvts, stepsParam, stepSlider1);

            beatLabel1.attachToComponent(&beatSlider1, false);
            beatLabel1.setText("Beats", juce::dontSendNotification);
            beatLabel1.setJustificationType(juce::Justification::centredTop);
            beatLabel1.setColour(juce::Label::textColourId, juce::Colours::black);
            beatAttach1 = std::make_unique<SliderAttachment>(apvts, beatsParam, beatSlider1);

            offsetLabel1.attachToComponent(&offsetSlider1, false);
            offsetLabel1.setText("Offset", juce::dontSendNotification);
            offsetLabel1.setJustificationType(juce::Justification::centredTop);
            offsetLabel1.setColour(juce::Label::textColourId, juce::Colours::black);
            offsetAttach1 = std::make_unique<SliderAttachment>(apvts, offsetParam, offsetSlider1);

            break;
        case 2:
            stepLabel2.attachToComponent(&stepSlider2, false);
            stepLabel2.setText("Steps", juce::dontSendNotification);
            stepLabel2.setJustificationType(juce::Justification::centredTop);
            stepLabel2.setColour(juce::Label::textColourId, juce::Colours::black);
            stepAttach2 = std::make_unique<SliderAttachment>(apvts, stepsParam, stepSlider2);

            beatLabel2.attachToComponent(&beatSlider2, false);
            beatLabel2.setText("Beats", juce::dontSendNotification);
            beatLabel2.setJustificationType(juce::Justification::centredTop);
            beatLabel2.setColour(juce::Label::textColourId, juce::Colours::black);
            beatAttach2 = std::make_unique<SliderAttachment>(apvts, beatsParam, beatSlider2);

            offsetLabel2.attachToComponent(&offsetSlider2, false);
            offsetLabel2.setText("Offset", juce::dontSendNotification);
            offsetLabel2.setJustificationType(juce::Justification::centredTop);
            offsetLabel2.setColour(juce::Label::textColourId, juce::Colours::black);
            offsetAttach2 = std::make_unique<SliderAttachment>(apvts, offsetParam, offsetSlider2);
            break;
        case 3:
            stepLabel3.attachToComponent(&stepSlider3, false);
            stepLabel3.setText("Steps", juce::dontSendNotification);
            stepLabel3.setJustificationType(juce::Justification::centredTop);
            stepLabel3.setColour(juce::Label::textColourId, juce::Colours::black);
            stepAttach3 = std::make_unique<SliderAttachment>(apvts, stepsParam, stepSlider3);

            beatLabel3.attachToComponent(&beatSlider3, false);
            beatLabel3.setText("Beats", juce::dontSendNotification);
            beatLabel3.setJustificationType(juce::Justification::centredTop);
            beatLabel3.setColour(juce::Label::textColourId, juce::Colours::black);
            beatAttach3 = std::make_unique<SliderAttachment>(apvts, beatsParam, beatSlider3);

            offsetLabel3.attachToComponent(&offsetSlider3, false);
            offsetLabel3.setText("Offset", juce::dontSendNotification);
            offsetLabel3.setJustificationType(juce::Justification::centredTop);
            offsetLabel3.setColour(juce::Label::textColourId, juce::Colours::black);
            offsetAttach3 = std::make_unique<SliderAttachment>(apvts, offsetParam, offsetSlider3);
            break;
        case 4:
            stepLabel4.attachToComponent(&stepSlider4, false);
            stepLabel4.setText("Steps", juce::dontSendNotification);
            stepLabel4.setJustificationType(juce::Justification::centredTop);
            stepLabel4.setColour(juce::Label::textColourId, juce::Colours::black);
            stepAttach4 = std::make_unique<SliderAttachment>(apvts, stepsParam, stepSlider4);

            beatLabel4.attachToComponent(&beatSlider4, false);
            beatLabel4.setText("Beats", juce::dontSendNotification);
            beatLabel4.setJustificationType(juce::Justification::centredTop);
            beatLabel4.setColour(juce::Label::textColourId, juce::Colours::black);
            beatAttach4 = std::make_unique<SliderAttachment>(apvts, beatsParam, beatSlider4);

            offsetLabel4.attachToComponent(&offsetSlider4, false);
            offsetLabel4.setText("Offset", juce::dontSendNotification);
            offsetLabel4.setJustificationType(juce::Justification::centredTop);
            offsetLabel4.setColour(juce::Label::textColourId, juce::Colours::black);
            offsetAttach4 = std::make_unique<SliderAttachment>(apvts, offsetParam, offsetSlider4);
            break;
        }
    }
}

void Knobs::toggleSliders()
{
    toggleRed.onStateChange = [this]() 
        {
            for (auto* slider : getSliders(0))
            {
                if (toggleRed.getToggleState())
                {
                    slider->setEnabled(true);
                    continue;
                }

                slider->setEnabled(false);
            }
        };

    toggleGreen.onStateChange = [this]()
        {
            for (auto* slider : getSliders(1))
            {
                if (toggleGreen.getToggleState())
                {
                    slider->setEnabled(true);
                    continue;
                }

                slider->setEnabled(false);
            }
        };

    toggleBlue.onStateChange = [this]()
        {
            for (auto* slider : getSliders(2))
            {
                if (toggleBlue.getToggleState())
                {
                    slider->setEnabled(true);
                    continue;
                }

                slider->setEnabled(false);
            }
        };

    toggleYellow.onStateChange = [this]()
        {
            for (auto* slider : getSliders(3))
            {
                if (toggleYellow.getToggleState())
                {
                    slider->setEnabled(true);
                    continue;
                }

                slider->setEnabled(false);
            }
        };
}

void Knobs::changeLimit(juce::AudioProcessorValueTreeState& apvts)
{
    // TODO

    stepSlider1.onValueChange = [this, &apvts]() 
        {
            if (beatSlider1.getValue() > stepSlider1.getValue())
            {
                beatSlider1.setValue(stepSlider1.getValue());
            }

            if (offsetSlider1.getValue() > stepSlider1.getValue())
            {
                offsetSlider1.setValue(stepSlider1.getValue());
            }

            auto beatRange = beatSlider1.getRange();
            auto sliderRange = offsetSlider1.getRange();
            beatSlider1.setRange(0, stepSlider1.getValue(), 1);
            offsetSlider1.setRange(0, stepSlider1.getValue(), 1);

            juce::Logger::writeToLog("Slider Value : " + juce::String(beatSlider1.getValue()));

            beatSlider1.repaint();
            offsetSlider1.repaint();
        };

    stepSlider1.onDragEnd = [this, &apvts]()
        {
            juce::Logger::writeToLog("APVTS Value : " + juce::String(apvts.getRawParameterValue("Beats 1")->load()));
        };

    stepSlider2.onDragEnd = [this]()
        {
            auto beatRange = beatSlider2.getRange();
            auto sliderRange = offsetSlider2.getRange();
            beatSlider2.setRange(0, stepSlider2.getValue(), 1);
            offsetSlider2.setRange(0, stepSlider2.getValue(), 1);
            beatSlider2.repaint();
            offsetSlider2.repaint();
        };

    stepSlider3.onDragEnd = [this]()
        {
            auto beatRange = beatSlider3.getRange();
            auto sliderRange = offsetSlider3.getRange();
            beatSlider3.setRange(0, stepSlider3.getValue(), 1);
            offsetSlider3.setRange(0, stepSlider3.getValue(), 1);
            beatSlider3.repaint();
            offsetSlider3.repaint();
        };

    stepSlider4.onDragEnd = [this]()
        {
            auto beatRange = beatSlider4.getRange();
            auto sliderRange = offsetSlider4.getRange();
            beatSlider4.setRange(0, stepSlider4.getValue(), 1);
            offsetSlider4.setRange(0, stepSlider4.getValue(), 1);
            beatSlider4.repaint();
            offsetSlider4.repaint();
        };
}