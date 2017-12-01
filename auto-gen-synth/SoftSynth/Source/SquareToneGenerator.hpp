#ifndef _SQUARETONEGENERATOR_H_
#define _SQUARETONEGENERATOR_H_

#include "ToneGenerator.hpp"


class SquareToneGenerator : public ToneGenerator {
  public:
    SquareToneGenerator() : sampleDelta(0), wavePosition(0) {}
    ~SquareToneGenerator() {}

    virtual double getSample() override {
      double output = (wavePosition >= 0.5 ? 1.0 : 0.0);
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

