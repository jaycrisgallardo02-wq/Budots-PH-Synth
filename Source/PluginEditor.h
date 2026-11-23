
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class BudotsPHSynthAudioProcessorEditor
    : public juce::AudioProcessorEditor
{
public:
    explicit BudotsPHSynthAudioProcessorEditor(
        BudotsPHSynthAudioProcessor&);

    ~BudotsPHSynthAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    BudotsPHSynthAudioProcessor& audioProcessor;

    juce::Label titleLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(
        BudotsPHSynthAudioProcessorEditor)
};
