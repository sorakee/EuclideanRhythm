
#include "Knobs.h"

Knobs::Knobs(juce::AudioProcessorValueTreeState& apvts)
{
    // 4 sets of knobs
    const int noOfComps = 4;

    // Initialise rotary slider components
    for (int i = 0; i < noOfComps; ++i)
    {
        for (auto* slider : getSliders(i))
        {
            addAndMakeVisible(slider);
        }
    }

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    // Make connection between rotary slider and parameter in 'apvts'
    for (int i = 0; i < noOfComps; ++i)
    {
        auto stepsParam = juce::String(std::string("Steps ") + std::to_string(i + 1));
        auto beatsParam = juce::String(std::string("Beats ") + std::to_string(i + 1));
        auto offsetParam = juce::String(std::string("Offset ") + std::to_string(i + 1));

        switch (i + 1)
        {
        case 1:
            stepAttach1 = std::make_unique<SliderAttachment>(apvts, stepsParam, stepSlider1);
            beatAttach1 = std::make_unique<SliderAttachment>(apvts, beatsParam, beatSlider1);
            offsetAttach1 = std::make_unique<SliderAttachment>(apvts, offsetParam, offsetSlider1);
            break;
        case 2:
            stepAttach2 = std::make_unique<SliderAttachment>(apvts, stepsParam, stepSlider2);
            beatAttach2 = std::make_unique<SliderAttachment>(apvts, beatsParam, beatSlider2);
            offsetAttach2 = std::make_unique<SliderAttachment>(apvts, offsetParam, offsetSlider2);
            break;
        case 3:
            stepAttach3 = std::make_unique<SliderAttachment>(apvts, stepsParam, stepSlider3);
            beatAttach3 = std::make_unique<SliderAttachment>(apvts, beatsParam, beatSlider3);
            offsetAttach3 = std::make_unique<SliderAttachment>(apvts, offsetParam, offsetSlider3);
            break;
        case 4:
            stepAttach4 = std::make_unique<SliderAttachment>(apvts, stepsParam, stepSlider4);
            beatAttach4 = std::make_unique<SliderAttachment>(apvts, beatsParam, beatSlider4);
            offsetAttach4 = std::make_unique<SliderAttachment>(apvts, offsetParam, offsetSlider4);
            break;
        }
    }
}

Knobs::~Knobs()
{
}

void Knobs::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightgrey);
}

void Knobs::resized()
{
    auto area = getLocalBounds();
    // Reserve bottom area of knobs area for playback buttons
    auto playbackButtonArea = area.removeFromBottom(area.getHeight() * 0.2);
    // Reserve remaining knobs area for upper area knobs
    auto knobsUpperArea = area.removeFromTop(area.getHeight() * 0.5);
    // Reserve upper left area for top-left knobs
    auto knobsUpperLeftArea = knobsUpperArea.removeFromLeft(knobsUpperArea.getWidth() * 0.5);
    // Reserve bottom left area for bottom-left knobs
    auto knobsBottomLeftArea = area.removeFromLeft(area.getWidth() * 0.5);

    // Top-left Knobs
    stepSlider1.setBounds(knobsUpperLeftArea.removeFromLeft(
        knobsUpperLeftArea.getWidth() * 0.33));
    beatSlider1.setBounds(knobsUpperLeftArea.removeFromLeft(
        knobsUpperLeftArea.getWidth() * 0.5));
    offsetSlider1.setBounds(knobsUpperLeftArea);

    // Top-right Knobs
    stepSlider2.setBounds(knobsUpperArea.removeFromLeft(
        knobsUpperArea.getWidth() * 0.33));
    beatSlider2.setBounds(knobsUpperArea.removeFromLeft(
        knobsUpperArea.getWidth() * 0.5));
    offsetSlider2.setBounds(knobsUpperArea);

    // Bottom-left Knobs
    stepSlider3.setBounds(knobsBottomLeftArea.removeFromLeft(
        knobsBottomLeftArea.getWidth() * 0.33));
    beatSlider3.setBounds(knobsBottomLeftArea.removeFromLeft(
        knobsBottomLeftArea.getWidth() * 0.5));
    offsetSlider3.setBounds(knobsBottomLeftArea);

    // Bottom-right Knobs
    stepSlider4.setBounds(area.removeFromLeft(
        area.getWidth() * 0.33));
    beatSlider4.setBounds(area.removeFromLeft(
        area.getWidth() * 0.5));
    offsetSlider4.setBounds(area);
}

std::vector<juce::Slider*> Knobs::getSliders(int compNum)
{
    std::vector<juce::Slider*> comps;

    switch (compNum + 1)
    {
    case 1:
        comps = {
            &stepSlider1,
            &beatSlider1,
            &offsetSlider1,
        };
        break;
    case 2:
        comps = {
            &stepSlider2,
            &beatSlider2,
            &offsetSlider2,
        };
        break;
    case 3:
        comps = {
            &stepSlider3,
            &beatSlider3,
            &offsetSlider3,
        };
        break;
    case 4:
        comps = {
            &stepSlider4,
            &beatSlider4,
            &offsetSlider4,
        };
        break;
    }

    return comps;
}
