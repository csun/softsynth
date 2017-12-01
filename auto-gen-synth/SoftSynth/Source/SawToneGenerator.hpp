#ifndef _SAWTONEGENERATOR_H_
#define _SAWTONEGENERATOR_H_

#include "ToneGenerator.hpp"


class SawToneGenerator : public ToneGenerator {
  public:
    SawToneGenerator() : sampleDelta(0), wavePosition(0) {}
    ~SawToneGenerator() {}

    virtual double getSample() override {
      double output = wavePosition;
      wavePosition = fmod(wavePosition + sampleDelta, 1.0f);

      return output;
    }

    virtual void setFrequency(double frequency) override {
      wavePosition = 0;
      sampleDelta = (frequency / sampleRate);
    }

  protected:
    double sampleDelta, wavePosition;
};

#endif

