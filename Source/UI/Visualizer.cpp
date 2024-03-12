/*
  ==============================================================================

    Visualizer.cpp
    Created: 3 Dec 2023 6:34:48pm
    Author:  User

  ==============================================================================
*/

#include "Visualizer.h"

Visualizer::Visualizer(juce::AudioProcessorValueTreeState& apvts)
{
    /*
    * 0 - Red
    * 1 - Green
    * 2 - Blue
    * 3 - Yellow
    */
    ellipses.resize(4);
    numOfEllipses = { 16, 16, 16, 16 };
    numOfBeats = { 16, 16, 16, 16 };
    toggle = { false, false, false, false };
    needles = {
        &needleRed,
        &needleGreen,
        &needleBlue,
        &needleYellow
    };

    for (int i = 0; i < 4; ++i)
    {
        float factor = 0.4f + (0.2f * i);
        juce::Colour colour;

        switch (i)
        {
        case 0:
            colour = juce::Colours::yellow;
            break;
        case 1:
            colour = juce::Colours::skyblue;
            break;
        case 2:
            colour = juce::Colours::limegreen;
            break;
        case 3:
            colour = juce::Colours::indianred;
            break;
        default:
            break;
        }

        // Ensures red needle (longest) is on top of other needles
        needles[3 - i]->setFactor(factor);
        needles[3 - i]->setColour(colour);
        addAndMakeVisible(needles[3 - i]);
    }
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

    juce::Path circlePath;

    // Draw the main circles
    for (int i = 0; i < 4; i++)
    {
        // Radius of main circles
        float radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) * 0.4f;
        radius *= 1 - (0.2f * i);
        circlePath.addEllipse(center.getX() - radius, center.getY() - radius, 2 * radius, 2 * radius);
    }
    
    g.setColour(juce::Colours::white);
    g.strokePath(circlePath, juce::PathStrokeType(2.5f));
}

void Visualizer::resized()
{
    juce::Rectangle<float> bounds = getLocalBounds().toFloat();
    juce::Point<float> center = bounds.getCentre();


    for (auto* needle : needles)
    {
        needle->setBounds(bounds.toNearestInt());
    }

    for (int color = 0; color < numOfEllipses.size(); ++color)
    {
        createEllipses(color);
        calculateEuclideanRhythm(numOfEllipses[color], numOfBeats[color], color);

        // Prevents ellipses from disappearing when resizing window
        if (toggle[color] == true) continue;

        toggleStatus(color, false);
    }
}

void Visualizer::createEllipses(int color)
{
    juce::Colour c;
    juce::Rectangle<float> bounds = getLocalBounds().toFloat();
    juce::Point<float> center = bounds.getCentre();

    // Radius of main circle
    float radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) * 0.4f;

    ellipses[color].clear();
    
    switch (color)
    {
    case 0:
        c = juce::Colours::indianred;
        break;
    case 1:
        c = juce::Colours::limegreen;
        radius *= 0.8f;
        break;
    case 2:
        c = juce::Colours::skyblue;
        radius *= 0.6f;
        break;
    case 3:
        c = juce::Colours::yellow;
        radius *= 0.4f;
        break;
    }

    for (int i = 0; i < numOfEllipses[color]; ++i)
    {
        float angle = (juce::MathConstants<float>::twoPi / numOfEllipses[color]) * i - juce::MathConstants<float>::pi / 2.0f;
        float ellipseX = center.getX() + radius * std::cos(angle);
        float ellipseY = center.getY() + radius * std::sin(angle);

        float ellipseWidth = 20.0f;
        float ellipseHeight = 20.0f;

        juce::Point<float> centerPos = juce::Point<float>(ellipseX, ellipseY);
        Ellipse* ellipse = new Ellipse(angle, radius, ellipseWidth, ellipseHeight, centerPos, c);

        addAndMakeVisible(ellipses[color].add(ellipse), 0);
    }
}

void Visualizer::calculateEuclideanRhythm(int steps, int beats, int color)
{
    // Clear previous beat settings
    for (auto* ellipse : ellipses[color])
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
        ellipses[color][i]->setBeat(pattern[i] == 1);
    }  
}

void Visualizer::setNumEllipses(int newNumEllipses, int newBeats, int color)
{
    if (newNumEllipses != numOfEllipses[color] || newBeats != numOfBeats[color])
    {
        numOfEllipses[color] = newNumEllipses;
        numOfBeats[color] = newBeats;
        // Reset needle when steps or beats change
        needles[color]->setAngle(-juce::MathConstants<float>::halfPi);
        createEllipses(color);
        calculateEuclideanRhythm(numOfEllipses[color], numOfBeats[color], color);
        repaint();
    }
}

Needle* Visualizer::getNeedle(int color)
{
    return needles[color];
}

void Visualizer::toggleStatus(int color, bool status)
{
    toggle[color] = status;
    
    for (auto* ellipse : ellipses[color])
    {
        if (status)
        {
            ellipse->setVisible(true);
        }
        else
        {
            ellipse->setVisible(false);
        }
    }

    if (status)
    {
        needles[color]->setVisible(true);
    }
    else
    {
        needles[color]->setVisible(false);
    }
}