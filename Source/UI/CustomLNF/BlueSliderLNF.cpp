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
    g.drawEllipse(rx, ry, rw, rw, radius * 0.1f);

    juce::Path p;
    auto pointerLength = radius * 0.75f;
    auto pointerThickness = radius * 0.2f;
    p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

    // Pointer
    g.setColour(juce::Colours::black);
    g.fillPath(p);

    juce::Rectangle<float> textArea;
    juce::String const text = juce::String(slider.getValue());
    
    auto font = g.getCurrentFont();
    font.setHeight(slider.proportionOfWidth(0.225f));
    g.setFont(font);

    if (slider.getTextBoxPosition() == juce::Slider::NoTextBox)
    {
        g.setColour(juce::Colours::black);
        textArea.setSize(2 * radius * 0.9f, font.getHeight() + 0.5f);
        textArea.setCentre(centreX, centreY);
        textArea.setY(centreY * 1.705f);
        g.fillRoundedRectangle(textArea, radius * 0.25f);

        // Text
        g.setColour(juce::Colours::white);
        g.drawFittedText(text, slider.getLocalBounds(), juce::Justification::centredBottom, 1);
    }
}
