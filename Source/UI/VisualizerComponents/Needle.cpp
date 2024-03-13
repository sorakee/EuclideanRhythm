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
    startTime = juce::Time::currentTimeMillis();
    colour = juce::Colours::indianred;
    samplesPerBeat = 0.0f;
    factor = 1.0f;
    steps = 8;
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

    length = length * factor;

    g.setColour(colour);
    g.drawLine(center.getX(), center.getY(),
               center.getX() + std::cos(angle) * length,
               center.getY() + std::sin(angle) * length, 5.0f);

}

void Needle::hiResTimerCallback()
{
    // Update the angle
    angle += juce::MathConstants<float>::twoPi / steps;

    // Ensure the angle stays within the range [0, 2*pi)
    if (juce::roundToInt(juce::radiansToDegrees(angle)) == juce::roundToInt(juce::radiansToDegrees(3.0f * juce::MathConstants<float>::halfPi)))
    {
        juce::int64 endTime = juce::Time::currentTimeMillis();
        juce::int64 timeTaken = endTime - startTime;

        float calc = (180.0f / juce::MathConstants<float>::pi) * angle;
        // DBG("Angle: " + juce::String(calc));
        // DBG("Start Time: " + juce::String(startTime));
        // DBG("End Time: " + juce::String(endTime));
        // DBG("Time taken: " + juce::String(timeTaken));

        startTime = endTime;

        angle = -juce::MathConstants<float>::halfPi;
    }

    // Trigger a repaint
    const juce::MessageManagerLock myLock;
    this->repaint();
}

void Needle::setColour(juce::Colour c)
{
    colour = c;
    this->repaint();
}

void Needle::setFactor(float fact)
{
    factor = fact;
    this->repaint();
}

void Needle::setAngle(float newAngle)
{
    angle = newAngle;
}

void Needle::setSteps(int newSteps)
{
    steps = newSteps;
}

void Needle::startNeedle(float interval)
{
    startTimer(juce::roundToInt(interval * 1000));
    startTime = juce::Time::currentTimeMillis();
}

void Needle::stopNeedle()
{
    stopTimer();
    angle = -juce::MathConstants<float>::halfPi;
    this->repaint();
}