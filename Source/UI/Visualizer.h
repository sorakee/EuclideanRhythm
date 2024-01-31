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

	void setNumEllipses(int newNumEllipses, int newBeats);
	Needle* getNeedle();

private:
	Needle needle;
	juce::OwnedArray<Ellipse> ellipses;
	void createEllipses();
	void calculateEuclideanRhythm(int steps, int beats);
	int numEllipses;
	int numBeats;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Visualizer)
};