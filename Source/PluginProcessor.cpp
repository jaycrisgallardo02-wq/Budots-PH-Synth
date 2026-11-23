
#include "PluginProcessor.h"
#include "PluginEditor.h"

BudotsPHSynthAudioProcessor::BudotsPHSynthAudioProcessor()
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    )
{
    synth.addSound(new juce::SynthesiserSound());
    synth.addVoice(new juce::SamplerVoice());
}

BudotsPHSynthAudioProcessor::~BudotsPHSynthAudioProcessor() {}

void BudotsPHSynthAudioProcessor::prepareToPlay(
    double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
}

void BudotsPHSynthAudioProcessor::releaseResources() {}

bool BudotsPHSynthAudioProcessor::isBusesLayoutSupported(
    const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() ==
           juce::AudioChannelSet::stereo();
}

void BudotsPHSynthAudioProcessor::processBlock(
    juce::AudioBuffer<float>& buffer,
    juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    buffer.clear();
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

juce::AudioProcessorEditor*
BudotsPHSynthAudioProcessor::createEditor()
{
    return new BudotsPHSynthAudioProcessorEditor(*this);
}

bool BudotsPHSynthAudioProcessor::hasEditor() const { return true; }

const juce::String BudotsPHSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BudotsPHSynthAudioProcessor::acceptsMidi() const { return true; }
bool BudotsPHSynthAudioProcessor::producesMidi() const { return false; }
bool BudotsPHSynthAudioProcessor::isMidiEffect() const { return false; }

double BudotsPHSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BudotsPHSynthAudioProcessor::getNumPrograms() { return 1; }
int BudotsPHSynthAudioProcessor::getCurrentProgram() { return 0; }
void BudotsPHSynthAudioProcessor::setCurrentProgram(int) {}

const juce::String BudotsPHSynthAudioProcessor::getProgramName(int)
{
    return {};
}

void BudotsPHSynthAudioProcessor::changeProgramName(
    int, const juce::String&) {}

void BudotsPHSynthAudioProcessor::getStateInformation(
    juce::MemoryBlock&) {}

void BudotsPHSynthAudioProcessor::setStateInformation(
    const void*, int) {}
