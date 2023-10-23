#pragma once

#include <JuceHeader.h>
#include "CustomLNF/GreenSliderLNF.h"

struct GreenSlider : juce::Slider
{
public:
    GreenSlider();
    ~GreenSlider();

    juce::Rectangle<int> getSliderBounds() const;
private:
    GreenSliderLNF lnf;
};
