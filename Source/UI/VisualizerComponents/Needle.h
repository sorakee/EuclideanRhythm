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
               private juce::HighResolutionTimer
{
public:
    Needle();
    ~Needle();

    void paint(juce::Graphics&) override;
    void hiResTimerCallback() override;

    void setAngle(float newAngle);
    void startNeedle();
    void stopNeedle();

private:
    float angle;
    juce::int64 startTime;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Needle)
};
