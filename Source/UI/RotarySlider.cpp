/*
  ==============================================================================

    RotarySlider.cpp
    Created: 18 Oct 2023 4:18:04pm
    Author:  akmal

  ==============================================================================
*/

#include "RotarySlider.h"

RotarySlider::RotarySlider() : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
    juce::Slider::TextEntryBoxPosition::TextBoxBelow)
{
    setLookAndFeel(&lnf);
}

RotarySlider::~RotarySlider()
{
    setLookAndFeel(nullptr);
}

juce::Rectangle<int> RotarySlider::getSliderBounds() const
{
    return getLocalBounds();
}