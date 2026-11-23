
#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace
{
    class BudotsSound : public juce::SynthesiserSound
    {
    public:
        bool appliesToNote(int) override { return true; }
        bool appliesToChannel(int) override { return true; }
    };

    class BudotsVoice : public juce::SynthesiserVoice
    {
    public:
        bool canPlaySound(juce::SynthesiserSound* sound) override
        {
            return dynamic_cast<BudotsSound*>(sound) != nullptr;
        }

        void startNote(int midiNoteNumber,
                       float velocity,
                       juce::SynthesiserSound*,
                       int) override
        {
            phase = 0.0;
            level = velocity;

            adsr.setSampleRate(getSampleRate());
            adsr.setParameters({ 0.01f, 0.10f, 0.8f, 0.20f });
            adsr.noteOn();

            auto frequency =
                juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);

            phaseIncrement =
                juce::MathConstants<double>::twoPi *
                frequency / getSampleRate();
        }

        void stopNote(float, bool allowTailOff) override
        {
            if (allowTailOff)
            {
                adsr.noteOff();
            }
            else
            {
                adsr.reset();
                clearCurrentNote();
            }
        }

        void pitchWheelMoved(int) override {}
        void controllerMoved(int, int) override {}

        void renderNextBlock(
            juce::AudioBuffer<float>& outputBuffer,
            int startSample,
            int numSamples) override
        {
            for (int i = 0; i < numSamples; ++i)
            {
                if (!adsr.isActive())
                {
                    clearCurrentNote();
                    break;
                }

                float envelope = adsr.getNextSample();

                float sample =
                    static_cast<float>(std::sin(phase)) *
                    level * envelope * 0.15f;

                phase += phaseIncrement;

                if (phase >= juce::MathConstants<double>::twoPi)
                    phase -= juce::MathConstants<double>::twoPi;

                for (int channel = 0;
                     channel < outputBuffer.getNumChannels();
                     ++channel)
                {
                    outputBuffer.addSample(
                        channel, startSample + i, sample);
                }
            }
        }

    private:
        double phase = 0.0;
        double phaseIncrement = 0.0;
        float level = 0.0f;

        juce::ADSR adsr;
    };
}

//==========================================================

BudotsPHSynthAudioProcessor::BudotsPHSynthAudioProcessor()
    : AudioProcessor(
        BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
            .withInput("Input",
                       juce::AudioChannelSet::stereo(), true)
#endif
            .withOutput("Output",
                        juce::AudioChannelSet::stereo(), true)
#endif
    )
{
    synth.setNoteStealingEnabled(true);
    synth.addSound(new BudotsSound());

    for (int i = 0; i < 12; ++i)
        synth.addVoice(new BudotsVoice());
}

BudotsPHSynthAudioProcessor::~BudotsPHSynthAudioProcessor() {}

void BudotsPHSynthAudioProcessor::prepareToPlay(
    double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(samplesPerBlock);
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

    synth.renderNextBlock(
        buffer, midiMessages, 0, buffer.getNumSamples());
}

juce::AudioProcessorEditor*
BudotsPHSynthAudioProcessor::createEditor()
{
    return new BudotsPHSynthAudioProcessorEditor(*this);
}

bool BudotsPHSynthAudioProcessor::hasEditor() const
{
    return true;
}

const juce::String BudotsPHSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BudotsPHSynthAudioProcessor::acceptsMidi() const { return true; }
bool BudotsPHSynthAudioProcessor::producesMidi() const { return false; }
bool BudotsPHSynthAudioProcessor::isMidiEffect() const { return false; }

double BudotsPHSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.25;
}

int BudotsPHSynthAudioProcessor::getNumPrograms() { return 1; }
int BudotsPHSynthAudioProcessor::getCurrentProgram() { return 0; }

void BudotsPHSynthAudioProcessor::setCurrentProgram(int) {}

const juce::String
BudotsPHSynthAudioProcessor::getProgramName(int)
{
    return {};
}

void BudotsPHSynthAudioProcessor::changeProgramName(
    int, const juce::String&) {}

void BudotsPHSynthAudioProcessor::getStateInformation(
    juce::MemoryBlock&) {}

void BudotsPHSynthAudioProcessor::setStateInformation(
    const void*, int) {}
