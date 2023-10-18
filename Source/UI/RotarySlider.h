#pragma once

#include <JuceHeader.h>
#include "CustomLNF/RedSliderLNF.h"

struct RotarySlider : juce::Slider
{
public:
    RotarySlider();
    ~RotarySlider();

    juce::Rectangle<int> getSliderBounds() const;
private:
    RedSliderLNF lnf;
};
