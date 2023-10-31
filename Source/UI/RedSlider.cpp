/*
  ==============================================================================

    RotarySlider.cpp
    Created: 18 Oct 2023 4:18:04pm
    Author:  akmal

  ==============================================================================
*/

#include "RedSlider.h"

RedSlider::RedSlider() : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
    juce::Slider::TextEntryBoxPosition::NoTextBox)
{
    setLookAndFeel(&lnf);
}

RedSlider::~RedSlider()
{
    setLookAndFeel(nullptr);
}

juce::Rectangle<int> RedSlider::getSliderBounds() const
{
    return getLocalBounds();
}