/*
  ==============================================================================

    RotarySlider.cpp
    Created: 18 Oct 2023 4:18:04pm
    Author:  akmal

  ==============================================================================
*/

#include "GreenSlider.h"

GreenSlider::GreenSlider() : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
    juce::Slider::TextEntryBoxPosition::NoTextBox)
{
    setLookAndFeel(&lnf);
    setEnabled(false);
}

GreenSlider::~GreenSlider()
{
    setLookAndFeel(nullptr);
}

juce::Rectangle<int> GreenSlider::getSliderBounds() const
{
    return getLocalBounds();
}