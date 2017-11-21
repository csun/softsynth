#ifndef _SINETONEGENERATOR_H_
#define _SINETONEGENERATOR_H_

#include "ToneGenerator.hpp"


class SineToneGenerator : public ToneGenerator {
  public:
    SineToneGenerator() : angleDelta(0), currentAngle(0) {}
    virtual double getSample() override {
      double output = std::sin(currentAngle);
      currentAngle = fmod(currentAngle + angleDelta, 2 * M_PI);
    }

    virtual void setFrequency(double frequency) {
      currentAngle = 0;
      angleDelta = (frequency / sampleRate) * 2 * M_PI;
    }
  protected:
    double angleDelta, currentAngle;
};

#endif
