#pragma once

#include <JuceHeader.h>
#include "CustomLNF/BlueSliderLNF.h"

struct BlueSlider : juce::Slider
{
public:
    BlueSlider();
    ~BlueSlider();

    juce::Rectangle<int> getSliderBounds() const;
private:
    BlueSliderLNF lnf;
};
