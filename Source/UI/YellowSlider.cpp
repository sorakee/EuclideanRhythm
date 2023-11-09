/*
  ==============================================================================

    RotarySlider.cpp
    Created: 18 Oct 2023 4:18:04pm
    Author:  akmal

  ==============================================================================
*/

#include "YellowSlider.h"

YellowSlider::YellowSlider() : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
    juce::Slider::TextEntryBoxPosition::NoTextBox)
{
    setLookAndFeel(&lnf);
    setEnabled(0);
}

YellowSlider::~YellowSlider()
{
    setLookAndFeel(nullptr);
}

juce::Rectangle<int> YellowSlider::getSliderBounds() const
{
    return getLocalBounds();
}