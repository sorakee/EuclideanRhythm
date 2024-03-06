/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EuclideanRhythmAudioProcessor::EuclideanRhythmAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts (*this, nullptr, "PARAMETERS", createParameterLayout())
                        , currentSampleRate (0.0f),
                          pattern (48)
#endif
{
    /*
    * 0 - Red
    * 1 - Green
    * 2 - Blue
    * 3 - Yellow
    */

    BPS = 0.0f;
    patterns = { pattern, pattern, pattern, pattern };

    currentAngle = { 0.0f, 0.0f, 0.0f, 0.0f };
    angleDelta = { 0.0f, 0.0f, 0.0f, 0.0f };

    sampleCount = { 0, 0, 0, 0 };
    patternTrack = { 0, 0, 0, 0 };
    count = { 0, 0, 0, 0 };
    interval = { 0, 0, 0, 0 };
    actualInterval = { 0, 0, 0, 0 };

    isSilent = { true, true, true, true };
    init = { true, true, true, true };
}

EuclideanRhythmAudioProcessor::~EuclideanRhythmAudioProcessor()
{
}

//==============================================================================
const juce::String EuclideanRhythmAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EuclideanRhythmAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EuclideanRhythmAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EuclideanRhythmAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EuclideanRhythmAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EuclideanRhythmAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EuclideanRhythmAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EuclideanRhythmAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String EuclideanRhythmAudioProcessor::getProgramName (int index)
{
    return {};
}

void EuclideanRhythmAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void EuclideanRhythmAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    currentSampleRate = sampleRate;
    updateAngleDelta();
    patterns[0] = calculateEuclideanRhythm(
        apvts.getRawParameterValue("Steps 1")->load(),
        apvts.getRawParameterValue("Beats 1")->load());
    patterns[1] = calculateEuclideanRhythm(
        apvts.getRawParameterValue("Steps 2")->load(),
        apvts.getRawParameterValue("Beats 2")->load());
    patterns[2] = calculateEuclideanRhythm(
        apvts.getRawParameterValue("Steps 3")->load(),
        apvts.getRawParameterValue("Beats 3")->load());
    patterns[3] = calculateEuclideanRhythm(
        apvts.getRawParameterValue("Steps 4")->load(),
        apvts.getRawParameterValue("Beats 4")->load());
}

void EuclideanRhythmAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EuclideanRhythmAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void EuclideanRhythmAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Retrieve BPM information from host, else defaults to 120 BPM
    juce::Optional<double> positionBPM;

    if (getPlayHead())
    {
        positionBPM = getPlayHead()->getPosition()->getBpm();
    }

    double currentBPM = (positionBPM.hasValue()) ? positionBPM.operator*() : 200.0;
    double currentBPS = currentBPM / 60.0;
    BPS = currentBPS;

    // TODO: Add speed parameter
    // Calculate interval in samples
    interval[0] = 60.0 / currentBPM * currentSampleRate;
    interval[1] = 60.0 / currentBPM * currentSampleRate;
    interval[2] = 60.0 / currentBPM * currentSampleRate;
    interval[3] = 60.0 / currentBPM * currentSampleRate;

    bool isRedOn = ((int)apvts.getRawParameterValue("Toggle Red")->load() == 1) ? true : false;
    bool isGreenOn = ((int)apvts.getRawParameterValue("Toggle Red")->load() == 1) ? true : false;
    bool isBlueOn = ((int)apvts.getRawParameterValue("Toggle Red")->load() == 1) ? true : false;
    bool isYellowOn = ((int)apvts.getRawParameterValue("Toggle Red")->load() == 1) ? true : false;

    for (int i = 0; i < 4; ++i)
    {
        initInterval(buffer, i);
    }

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());
    
    patterns[0] = calculateEuclideanRhythm(
        apvts.getRawParameterValue("Steps 1")->load(),
        apvts.getRawParameterValue("Beats 1")->load());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    // Count total number of samples

    auto* leftChannel = buffer.getWritePointer(0);
    auto* rightChannel = buffer.getWritePointer(1);

    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        float currentSample = calculateSample(currentAngle[0], angleDelta[0]);

        // Output sound wave to the left channel buffer
        leftChannel[sample] = (isSilent[0] || !isRedOn) ? 0.0f : (0.125f * currentSample);
        rightChannel[sample] = (isSilent[0] || !isRedOn) ? 0.0f : (0.125f * currentSample);
    }

    sampleCount[0] += buffer.getNumSamples();

    // DBG(sampleCount);

    if (sampleCount[0] * 2 >= interval[0] && isRedOn)
    {
        // Retrieve actual interval for synchronization
        actualInterval[0] = sampleCount[0] * 2;
        sampleCount[0] = 0;
        currentAngle[0] = 0.0f;

        isSilent[0] = (patterns[0][patternTrack[0]]) ? !isSilent[0] : true;

        patternTrack[0] += (count[0] == 1) ? 1 : 0;

        if (patternTrack[0] >= apvts.getRawParameterValue("Steps 1")->load())
        {
            patternTrack[0] = 0;
        }

        DBG(patternTrack[0]);

        // Prevents double counting due to sample blocks being processed in each channel
        // Therefore, sample count * number of channels
        count[0] = (count[0] % 2 != 0) ? 0 : count[0] + 1;
    }

    if (!isRedOn)
    {
        reset();
    }
}

void EuclideanRhythmAudioProcessor::initInterval(juce::AudioBuffer<float>& buffer, int color)
{
    while (init[color])
    {
        if (sampleCount[color] * 2 >= interval[color])
        {
            actualInterval[color] = sampleCount[color] * 2;
            sampleCount[color] = interval[color];
            init[color] = false;
            break;
        }

        sampleCount[color] += buffer.getNumSamples();
    }
}

void EuclideanRhythmAudioProcessor::reset()
{
    sampleCount[0] = interval[0];
    patternTrack[0] = 0;
    count[0] = 0;
    currentAngle[0] = 0.0f;
    isSilent[0] = true;
}

float EuclideanRhythmAudioProcessor::calculateSample(float &currentAngle, float &angleDelta)
{
    float currentSample = std::sin(currentAngle);
    currentAngle += angleDelta;
    currentAngle = (currentAngle >= juce::MathConstants<float>::twoPi) ?
        currentAngle - juce::MathConstants<float>::twoPi : currentAngle;

    return currentSample;
}

//==============================================================================
bool EuclideanRhythmAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* EuclideanRhythmAudioProcessor::createEditor()
{
    return new EuclideanRhythmAudioProcessorEditor (*this, apvts);
    // Debugging purposes
    // return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void EuclideanRhythmAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void EuclideanRhythmAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

juce::AudioProcessorValueTreeState::ParameterLayout 
    EuclideanRhythmAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    const int noOfComps = 4;
    const std::vector<juce::String> colours{"Red", "Green", "Blue", "Yellow"};

    for (int i = 0; i < noOfComps; ++i)
    {
        auto stepsParam = juce::String(std::string("Steps ") + std::to_string(i + 1));
        auto beatsParam = juce::String(std::string("Beats ") + std::to_string(i + 1));
        auto offsetParam = juce::String(std::string("Offset ") + std::to_string(i + 1));
        layout.add(std::make_unique<juce::AudioParameterInt>(stepsParam, stepsParam, 1, 48, 16));
        layout.add(std::make_unique<juce::AudioParameterInt>(beatsParam, beatsParam, 0, 48, 16));
        layout.add(std::make_unique<juce::AudioParameterInt>(offsetParam, offsetParam, 0, 48, 0));
    }

    for (juce::String c : colours)
    {
        auto toggleParam = juce::String(juce::String("Toggle ") + c);
        layout.add(std::make_unique<juce::AudioParameterBool>(toggleParam, toggleParam, false));
    }

    // TODO (OPTIONAL) : Add velocity/speed parameter to manipulate 
    // how fast it takes to move between steps
    
    return layout;
}

std::vector<bool> EuclideanRhythmAudioProcessor::calculateEuclideanRhythm(int steps, int beats)
{
    // Buffer Size
    const int bufferSize = 48;

    // Initialize euclidean rhythm pattern
    std::vector<bool> pattern(bufferSize, false);

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
        pattern[i] = (rhythm[i] == '1') ? true : false;
    }

    return pattern;
}

void EuclideanRhythmAudioProcessor::updateAngleDelta()
{
    const float frequency = 440.0f; // A4
    angleDelta[0] = juce::MathConstants<float>::twoPi * (frequency / currentSampleRate);
}

float EuclideanRhythmAudioProcessor::getInterval()
{
    return actualInterval[0] / currentSampleRate;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EuclideanRhythmAudioProcessor();
}
