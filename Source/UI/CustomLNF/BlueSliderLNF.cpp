/*
  ==============================================================================

    SliderLNF.cpp
    Created: 18 Oct 2023 3:47:35pm
    Author:  akmal

  ==============================================================================
*/

#include "BlueSliderLNF.h"

BlueSliderLNF::BlueSliderLNF()
{
}

BlueSliderLNF::~BlueSliderLNF()
{
}

void BlueSliderLNF::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
    const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
{
    auto radius = (float)juce::jmin(width / 2, height / 2) - 10.0f;
    auto centreX = (float)x + (float)width * 0.5f;
    auto centreY = (float)y + (float)height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    // Fill Ellipse
    g.setColour(juce::Colours::skyblue);
    g.fillEllipse(rx, ry, rw, rw);

    // Outline of Ellipse
    g.setColour(juce::Colours::black);
    g.drawEllipse(rx, ry, rw, rw, 1.0f);

    juce::Path p;
    auto pointerLength = radius * 0.33f;
    auto pointerThickness = 2.0f;
    p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

    // Pointer
    g.setColour(juce::Colours::black);
    g.fillPath(p);
}
