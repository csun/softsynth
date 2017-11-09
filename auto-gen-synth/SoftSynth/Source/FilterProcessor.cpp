#define _USE_MATH_DEFINES

#include "FilterProcessor.h"
#include <cmath>
#include <iostream>


FilterProcessor::FilterProcessor() {
  addParameter(cutoff = new AudioParameterFloat("cutoff", "Cutoff", 0.0f, 20000.0f, 1000.0f));
  addParameter(resonance = new AudioParameterFloat("resonance", "Resonance", 0.707f, 4.0f, 33.0f));
  addParameter(isLpf = new AudioParameterBool("isLpf", "Low Pass", true));

  // NOTE Because of the way the algorithm works, both the in and out delay lines
  // must have exactly two values in them at all times.
  inDelay.push(0.0f);
  inDelay.push(0.0f);
  outDelay.push(0.0f);
  outDelay.push(0.0f);
}

FilterProcessor::~FilterProcessor() {
  delete cutoff;
  delete resonance;
  delete isLpf;
}

void FilterProcessor::prepareToPlay(double sampleRate, int samplesPerBlockExpected) {
  currentSampleRate = sampleRate;
}

void FilterProcessor::releaseResources() {
}

void FilterProcessor::processBlock(AudioSampleBuffer &buffer, MidiBuffer &midi) {
  updateCoefficients();

  float* writeBuf = buffer.getWritePointer(0, 0);
  for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
    processSample(writeBuf[sample]);
  }
}

void FilterProcessor::processSample(float &sample) {
  float in = sample;

  sample = (a0 * in) + (a1 * inDelay.back()) + (a2 * inDelay.front());
  sample -= ((b1 * outDelay.back()) + (b2 * outDelay.front()));
  inDelay.pop();
  outDelay.pop();

  inDelay.push(in);
  outDelay.push(sample);
}

void FilterProcessor::updateCoefficients() {
  w = (2 * M_PI * cutoff->get()) / currentSampleRate;
  d = 1 / resonance->get();
  beta = ( (1 - (d/2) * sin(w)) / (1 + (d/2) * sin(w)) ) / 2;
  gamma = (0.5 + beta) * cos(w);

  if(isLpf->get()) {
    a0 = (0.5 + beta - gamma) / 2;
    a1 = 0.5 + beta - gamma;
  } else {
    a0 = (0.5 + beta + gamma) / 2;
    a1 = -(0.5 + beta + gamma);
  }

  a2 = a0;
  b1 = -2 * gamma;
  b2 = 2 * beta;
}
