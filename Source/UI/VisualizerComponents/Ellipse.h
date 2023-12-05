/*
  ==============================================================================

    Ellipse.h
    Created: 4 Dec 2023 2:19:16pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Ellipse : public juce::Component
{
public:
    Ellipse(float angle, 
            float radius, 
            float ellipseWidth, 
            float ellipseHeight,
            juce::Point<float> position);

    void paint(juce::Graphics&) override;

    void setBeat(bool isBeat);

private:
    float angle;
    float radius;
    float ellipseWidth;
    float ellipseHeight;
    juce::Point<float> position;
    bool beat;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Ellipse)
};
