/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class EuclideanRhythmAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    EuclideanRhythmAudioProcessor();
    ~EuclideanRhythmAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    float getInterval(int color);
    void setInit(int color, bool initStatus);
    void reset(int color);

private:
    juce::AudioProcessorValueTreeState::ParameterLayout 
        createParameterLayout();
    juce::AudioProcessorValueTreeState apvts;
    juce::AudioPlayHead* playHead;

    void updateAngleDelta(int color, float frequency);
    void rhythmTracker(int color, bool toggle);
    void initInterval(juce::AudioBuffer<float>& buffer, int color);
    float calculateSample(int color);

    // Euclidean Algorithm
    std::vector<bool> calculateEuclideanRhythm (int steps, int beats, int offset);
    std::vector<bool> pattern;
    std::vector<std::vector<bool>> patterns;
    std::vector<bool> isSilent, init;
    std::vector<int> sampleCount, patternTrack, count, interval, actualInterval;
    std::vector<float> currentAngle, angleDelta;

    float currentSampleRate, BPS, fadeFactor, fadeStep;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EuclideanRhythmAudioProcessor)
};
