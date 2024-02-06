/*
  ==============================================================================

    Visualizer.cpp
    Created: 3 Dec 2023 6:34:48pm
    Author:  User

  ==============================================================================
*/

#include "Visualizer.h"

Visualizer::Visualizer(juce::AudioProcessorValueTreeState& apvts) :
    numEllipses(16), numBeats(16)
{
    addAndMakeVisible(needle);
}

Visualizer::~Visualizer()
{
}

void Visualizer::paint(juce::Graphics& g)
{
    // Visualizer background colour
    g.fillAll(juce::Colours::black);

    juce::Rectangle<float> bounds = getLocalBounds().toFloat();
    juce::Point<float> center = bounds.getCentre();

    // Radius of main circle
    float radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) * 0.4f;

    // Draw the main circle
    juce::Path circlePath;
    circlePath.addEllipse(center.getX() - radius, center.getY() - radius, 2 * radius, 2 * radius);
    g.setColour(juce::Colours::white);
    g.strokePath(circlePath, juce::PathStrokeType(2.5f));
}

void Visualizer::resized()
{
    juce::Rectangle<float> bounds = getLocalBounds().toFloat();
    juce::Point<float> center = bounds.getCentre();

    needle.setBounds(bounds.toNearestInt());

    createEllipses();
    calculateEuclideanRhythm(numEllipses, numBeats);
}

void Visualizer::createEllipses()
{
    juce::Rectangle<float> bounds = getLocalBounds().toFloat();
    juce::Point<float> center = bounds.getCentre();

    // Radius of main circle
    float radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) * 0.4f;

    ellipses.clear();

    for (int i = 0; i < numEllipses; ++i)
    {
        float angle = (juce::MathConstants<float>::twoPi / numEllipses) * i - juce::MathConstants<float>::pi / 2.0f;
        float ellipseX = center.getX() + radius * std::cos(angle);
        float ellipseY = center.getY() + radius * std::sin(angle);

        float ellipseWidth = 20.0f;
        float ellipseHeight = 20.0f;

        juce::Point<float> centerPos = juce::Point<float>(ellipseX, ellipseY);
        Ellipse* ellipse = new Ellipse(angle, radius, ellipseWidth, ellipseHeight, centerPos);

        addAndMakeVisible(ellipses.add(ellipse));
    }
}

void Visualizer::calculateEuclideanRhythm(int steps, int beats)
{
    // Clear previous beat settings
    for (auto* ellipse : ellipses)
    {
        ellipse->setBeat(false);
    }

    // Calculate Euclidean rhythm
    std::vector<int> pattern(steps, 0);

    // Each iteration is a process of pairing strings X and Y and the remainder from the pairings
    // X will hold the "dominant" pair (the pair that there are more of)
    std::string x = "1";
    int x_amount = beats;

    std::string y = "0";
    int y_amount = steps - beats;

    // iterate as long as the non dominant pair can be paired 
    // (if there is 1 Y left, all we can do is pair it with however many Xs are left, so we're done)
    while (x_amount > 1 && y_amount > 1)
    {
        // Placeholder variables
        int x_temp = x_amount;
        int y_temp = y_amount;
        std::string y_copy = y;

        // Check which is the dominant pair 
        if (x_temp >= y_temp)
        {
            // Set the new number of pairs for X and Y
            x_amount = y_temp;
            y_amount = x_temp - y_temp;

            // The previous dominant pair becomes the new non dominant pair
            y = x;
        }
        else
        {
            x_amount = x_temp;
            y_amount = y_temp - x_temp;
        }

        // Create the new dominant pair by combining the previous pairs
        x = x + y_copy;
    }

    // By this point, we have strings X and Y formed through a series of pairings of the initial strings "1" and "0"
    // X is the final dominant pair and Y is the second to last dominant pair
    std::string rhythm;
    for (int i = 1; i <= x_amount; i++)
        rhythm += x;
    for (int i = 1; i <= y_amount; i++)
        rhythm += y;
    
    // Set beat status based on Euclidean rhythm
    for (int i = 0; i < rhythm.length(); ++i)
    {
        pattern[i] = (rhythm[i] == '1') ? 1 : 0;
        ellipses[i]->setBeat(pattern[i] == 1);
    }  
}

void Visualizer::setNumEllipses(int newNumEllipses, int newBeats)
{
    if (newNumEllipses != numEllipses || newBeats != numBeats)
    {
        numEllipses = newNumEllipses;
        numBeats = newBeats;
        // Reset needle when steps or beats change
        needle.setAngle(-juce::MathConstants<float>::halfPi);
        createEllipses();
        calculateEuclideanRhythm(numEllipses, numBeats);
        repaint();
    }
}

Needle* Visualizer::getNeedle()
{
    return &needle;
}