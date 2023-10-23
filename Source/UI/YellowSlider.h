#pragma once

#include <JuceHeader.h>
#include "CustomLNF/YellowSliderLNF.h"

struct YellowSlider : juce::Slider
{
public:
    YellowSlider();
    ~YellowSlider();

    juce::Rectangle<int> getSliderBounds() const;
private:
    YellowSliderLNF lnf;
};
