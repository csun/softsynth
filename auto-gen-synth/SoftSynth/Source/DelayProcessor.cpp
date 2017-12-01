#include "DelayProcessor.h"
#include <cmath>
#include <iostream>


DelayProcessor::DelayProcessor() {
  addParameter(isOn = new AudioParameterBool(
        "isOn", "On", false));
  addParameter(time = new AudioParameterFloat(
        "time", "Time (ms)", 0.0f, 1000.0f, 200.0f));
  addParameter(feedback = new AudioParameterFloat(
        "feedback", "Feedback", 0.0f, 1.0f, 0.25f));
  addParameter(mix = new AudioParameterFloat(
        "mix", "Mix", 0.0f, 1.0f, 0.5f));
}

DelayProcessor::~DelayProcessor() {
  // NOTE Base class handles deletion of all parameters added with addParameter.
  // We do not need to free them manually.
}

void DelayProcessor::prepareToPlay(double sampleRate, int samplesPerBlockExpected) {
  currentSampleRate = sampleRate;
}

void DelayProcessor::releaseResources() {
}

void DelayProcessor::processBlock(AudioSampleBuffer &buffer, MidiBuffer &midi) {
  if(isOn->get()) {
    resizeDelayLine();

    float* writeBuf = buffer.getWritePointer(0, 0);
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
      processSample(writeBuf[sample]);
    }
  }
  else {
    delayLine.clear();
  }
}

void DelayProcessor::processSample(float &sample) {
  float mixAmt = mix->get();
  float feedbackAmt = feedback->get();
  float in = sample;
  float delaySample = delayLine.front();

  delayLine.pop_front();
  delayLine.push_back(
      (in * (1.0f - feedbackAmt)) + (delaySample * feedbackAmt));
  
  sample = (in * (1.0f - mixAmt)) + (delaySample * mixAmt);
}

void DelayProcessor::resizeDelayLine() {
  int desiredSize = std::ceil(
      (time->get() / 1000) * currentSampleRate);

  while(delayLine.size() < desiredSize) {
    delayLine.push_front(0.0f);
  }
  while(delayLine.size() > desiredSize) {
    delayLine.pop_front();
  }
}
