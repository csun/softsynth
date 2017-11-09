#ifndef _FILTERPROCESSOR_H_
#define _FILTERPROCESSOR_H_

#include "../JuceLibraryCode/JuceHeader.h"
#include <queue>


class FilterProcessor : public AudioProcessor {
  public:
    FilterProcessor();
    ~FilterProcessor();

    void prepareToPlay(double sampleRate, int samplesPerBlockExpected) override;
    void releaseResources() override;
    void processBlock(AudioSampleBuffer &buffer, MidiBuffer &midi) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override { return new GenericAudioProcessorEditor(this); }
    bool hasEditor() const override               { return true; }

    const String getName() const override               { return "Filter"; }
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
    void updateCoefficients();

    AudioParameterFloat *cutoff;
    AudioParameterFloat *resonance;
    AudioParameterBool *isLpf;

    float currentSampleRate;
    float w, d, beta, gamma;
    float a0, a1, a2, b1, b2;
    std::queue<float> inDelay;
    std::queue<float> outDelay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterProcessor)
};

#endif
