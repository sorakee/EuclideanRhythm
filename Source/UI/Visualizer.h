/*
  ==============================================================================

    Visualizer.h
    Created: 3 Dec 2023 6:34:48pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "VisualizerComponents/Ellipse.h"
#include "VisualizerComponents/Needle.h"

class Visualizer : public juce::Component
{
public:
	Visualizer(juce::AudioProcessorValueTreeState&);
	~Visualizer() override;

	void paint(juce::Graphics&) override;
	void resized() override;

	void setNumEllipses(int newNumEllipses, int newBeats, int color, int newOffset);
	void toggleStatus(int color, bool status);
	Needle* getNeedle(int color);

private:
	Needle needleRed, needleGreen, needleBlue, needleYellow;

	void createEllipses(int color);
	void calculateEuclideanRhythm(int steps, int beats, int color, int offset);

	std::vector<juce::OwnedArray<Ellipse>> ellipses;
	std::vector<Needle*> needles;
	std::vector<int> numOfEllipses;
	std::vector<int> numOfBeats;
	std::vector<int> offsetVals;
	std::vector<bool> toggle;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Visualizer)
};