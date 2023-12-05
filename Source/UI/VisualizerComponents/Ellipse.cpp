/*
  ==============================================================================

    Ellipse.cpp
    Created: 4 Dec 2023 2:19:16pm
    Author:  User

  ==============================================================================
*/

#include "Ellipse.h"

Ellipse::Ellipse(float angle, 
                 float radius, 
                 float ellipseWidth, 
                 float ellipseHeight,
                 juce::Point<float> pos)
        : angle(angle), 
          radius(radius), 
          ellipseWidth(ellipseWidth), 
          ellipseHeight(ellipseHeight),
          position(pos),
          beat(false)
{
    setSize(ellipseWidth, ellipseHeight);
    setCentrePosition((int)pos.x, (int)pos.y);
}

void Ellipse::paint(juce::Graphics& g)
{
    juce::Rectangle<float> ellipseBounds(0, 0, ellipseWidth, ellipseHeight);

    g.setColour(beat ? juce::Colours::indianred : juce::Colours::white);
    
    g.fillEllipse(ellipseBounds);
}

void Ellipse::setBeat(bool isBeat)
{
    this->beat = isBeat;
}