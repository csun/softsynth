#ifndef _SINETONEGENERATOR_H_
#define _SINETONEGENERATOR_H_

#include "ToneGenerator.hpp"


class SineToneGenerator : public ToneGenerator {
  public:
    SineToneGenerator() : angleDelta(0), currentAngle(0) {}
    ~SineToneGenerator() {}

    virtual double getSample() override {
      double output = std::sin(currentAngle);
      currentAngle = fmod(currentAngle + angleDelta, 2 * M_PI);

      return output;
    }

    virtual void setFrequency(double frequency) override {
      currentAngle = 0;
      angleDelta = (frequency / sampleRate) * 2 * M_PI;
    }
  protected:
    double angleDelta, currentAngle;
};

#endif
