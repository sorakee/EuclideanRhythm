/*
  ==============================================================================

    Toggle.cpp
    Created: 30 Oct 2023 5:17:03pm
    Author:  akmal

  ==============================================================================
*/

#include "Toggle.h"

Toggle::Toggle() : juce::ShapeButton(juce::String("Toggle"),  
                                     juce::Colours::red,
                                     juce::Colours::darkred,
                                     juce::Colours::green)
{
    juce::Path buttonShape;
    buttonShape.addEllipse (0, 0, 100, 100);
    setOutline (juce::Colours::black, 1.5f);
    setShape (buttonShape, false, true, false);
    juce::BorderSize<int> border(5, 0, 0, 0);
    setBorderSize(border);
    setToggleable(true);
    setClickingTogglesState(true);
    shouldUseOnColours(true);
    setOnColours(juce::Colours::lightgreen,
                 juce::Colours::green,
                 juce::Colours::red);

    // DEBUGGING
    this->onClick = [this]
        {
            juce::String state = (this->getToggleState()) ? "ON" : "OFF";
            juce::Logger::writeToLog(state);
        };
}

Toggle::~Toggle() 
{
}