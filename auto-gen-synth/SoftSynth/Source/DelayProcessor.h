#ifndef _DELAYPROCESSOR_H_
#define _DELAYPROCESSOR_H_

#include "../JuceLibraryCode/JuceHeader.h"
#include <deque>


class DelayProcessor : public AudioProcessor {
  public:
    DelayProcessor();
    ~DelayProcessor();

    void prepareToPlay(double sampleRate, int samplesPerBlockExpected) override;
    void releaseResources() override;
    void processBlock(AudioSampleBuffer &buffer, MidiBuffer &midi) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override { return new GenericAudioProcessorEditor(this); }
    bool hasEditor() const override               { return true; }

    const String getName() const override               { return "Delay"; }
    bool acceptsMidi() const override                   { return false; }
    bool producesMidi() const override                  { return false; }
    double getTailLengthSeconds() const override        { return 0; }

    int getNumPrograms() override                          { return 1; }
    int getCurrentProgram() override                       { return 0; }
    void setCurrentProgram (int) override                  {}
    const String getProgramName (int) override             { return String(); }
    void changeProgramName (int , const String& ) override {}

    void getStateInformation(MemoryBlock& destData) override {}
    void setStateInformation(const void *data, int sizeInBytes) override {}

  protected:
    void processSample(float &sample);
    void resizeDelayLine();

    AudioParameterFloat *time;
    AudioParameterFloat *feedback;
    AudioParameterFloat *mix;
    AudioParameterBool *isOn;

    float currentSampleRate;
    std::deque<float> delayLine;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayProcessor)
};

#endif

