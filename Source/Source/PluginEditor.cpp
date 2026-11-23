
#include "PluginEditor.h"

BudotsPHSynthAudioProcessorEditor::
BudotsPHSynthAudioProcessorEditor(
    BudotsPHSynthAudioProcessor& p)
    : AudioProcessorEditor(&p),
      audioProcessor(p)
{
    titleLabel.setText(
        "BUDOTS PH SYNTH",
        juce::dontSendNotification);

    titleLabel.setFont(
        juce::Font(28.0f, juce::Font::bold));

    titleLabel.setJustificationType(
        juce::Justification::centred);

    titleLabel.setColour(
        juce::Label::textColourId,
        juce::Colours::white);

    addAndMakeVisible(titleLabel);

    setSize(600, 400);
}

BudotsPHSynthAudioProcessorEditor::
~BudotsPHSynthAudioProcessorEditor() {}

void BudotsPHSynthAudioProcessorEditor::paint(
    juce::Graphics& g)
{
    g.fillAll(juce::Colour(25, 20, 40));

    g.setColour(juce::Colour(255, 80, 180));

    g.fillRoundedRectangle(
        getLocalBounds().toFloat().reduced(15),
        15.0f);

    g.setColour(juce::Colour(25, 20, 40));

    g.fillRoundedRectangle(
        getLocalBounds().toFloat().reduced(19),
        12.0f);
}

void BudotsPHSynthAudioProcessorEditor::resized()
{
    titleLabel.setBounds(20, 30, 560, 60);
}
