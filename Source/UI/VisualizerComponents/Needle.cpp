/*
  ==============================================================================

    Needle.cpp
    Created: 4 Dec 2023 8:44:21pm
    Author:  User

  ==============================================================================
*/

#include "Needle.h"

Needle::Needle() : angle(-juce::MathConstants<float>::halfPi)
{
}

Needle::~Needle()
{
    stopTimer();
}

void Needle::paint(juce::Graphics& g)
{
    juce::Rectangle<float> bounds = getLocalBounds().toFloat();
    juce::Point<float> center = bounds.getCentre();
    float length = juce::jmin(bounds.getWidth(), bounds.getHeight()) * 0.4f;

    g.setColour(juce::Colours::indianred);
    g.drawLine(center.getX(), center.getY(),
               center.getX() + std::cos(angle) * length,
               center.getY() + std::sin(angle) * length, 5.0f);

}

void Needle::hiResTimerCallback()
{
    // Update the angle
    angle += juce::MathConstants<float>::twoPi / (16.0f);

    // Ensure the angle stays within the range [0, 2*pi)
    if (angle >= 3.0f * juce::MathConstants<float>::halfPi)
    {
        juce::int64 endTime = juce::Time::currentTimeMillis();
        juce::int64 timeTaken = endTime - startTime;

        float calc = (180.0f / juce::MathConstants<float>::twoPi) * angle;
        DBG("Angle: " + juce::String(calc));
        DBG("Start Time: " + juce::String(startTime));
        DBG("End Time: " + juce::String(endTime));
        DBG("Time taken: " + juce::String(timeTaken));

        startTime = endTime;

        angle = -juce::MathConstants<float>::halfPi;
    }

    // TODO: Reset needle to default position and stop timer if this pattern is terminated

    // Trigger a repaint
    const juce::MessageManagerLock myLock;
    this->repaint();
}

void Needle::setAngle(float newAngle)
{
    angle = newAngle;
}

void Needle::startNeedle()
{
    // Time = 1 / frequency (Hz), 60 Hz
    startTimer(1000);
    startTime = juce::Time::currentTimeMillis();
}

void Needle::stopNeedle()
{
    stopTimer();
    angle = -juce::MathConstants<float>::halfPi;
    this->repaint();
}