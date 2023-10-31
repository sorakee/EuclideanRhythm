/*
  ==============================================================================

    RotarySlider.cpp
    Created: 18 Oct 2023 4:18:04pm
    Author:  akmal

  ==============================================================================
*/

#include "BlueSlider.h"

BlueSlider::BlueSlider() : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
    juce::Slider::TextEntryBoxPosition::NoTextBox)
{
    setLookAndFeel(&lnf);
}

BlueSlider::~BlueSlider()
{
    setLookAndFeel(nullptr);
}

juce::Rectangle<int> BlueSlider::getSliderBounds() const
{
    return getLocalBounds();
}