#pragma once

#include <JuceHeader.h>
#include "CustomLNF/RedSliderLNF.h"

struct RedSlider : juce::Slider
{
public:
    RedSlider();
    ~RedSlider();

    juce::Rectangle<int> getSliderBounds() const;
private:
    RedSliderLNF lnf;
};
