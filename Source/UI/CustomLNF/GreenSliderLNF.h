/*
  ==============================================================================

    SliderLNF.h
    Created: 18 Oct 2023 3:47:35pm
    Author:  akmal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class GreenSliderLNF : public juce::LookAndFeel_V4
{
public:
    GreenSliderLNF();
    ~GreenSliderLNF();

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override;
};
