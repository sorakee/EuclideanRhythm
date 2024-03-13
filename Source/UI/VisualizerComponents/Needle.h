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

    void setColour(juce::Colour newColour);
    void setFactor(float newFactor);
    void setAngle(float newAngle);
    void setSteps(int newSteps);
    void startNeedle(float interval);
    void resetNeedle();
    void stopNeedle();

private:
    int steps;
    float angle, samplesPerBeat, factor, prevInterval;
    juce::int64 startTime;
    juce::Colour colour;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Needle)
};
