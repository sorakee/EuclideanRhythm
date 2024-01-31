/*
  ==============================================================================

    Needle.h
    Created: 4 Dec 2023 8:44:21pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Needle : public juce::Component,
               private juce::Timer
{
public:
    Needle();

    void paint(juce::Graphics&) override;
    void timerCallback() override;

    void setAngle(float newAngle);

private:
    float angle;
    juce::int64 startTime;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Needle)
};
