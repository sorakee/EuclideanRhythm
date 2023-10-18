/*
  ==============================================================================

    SliderLNF.h
    Created: 18 Oct 2023 3:47:35pm
    Author:  akmal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class RedSliderLNF : public juce::LookAndFeel_V4
{
public:
    RedSliderLNF();
    ~RedSliderLNF();

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override;
};
