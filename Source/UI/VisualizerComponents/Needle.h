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

    void setColour(juce::Colour);
    void setFactor(float);
    void setAngle(float);
    void setSteps(int);
    void startNeedle(float);
    void stopNeedle();

private:
    int steps;
    float angle, samplesPerBeat, factor;
    juce::int64 startTime;
    juce::Colour colour;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Needle)
};
