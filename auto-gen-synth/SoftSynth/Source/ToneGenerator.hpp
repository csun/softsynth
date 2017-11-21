#ifndef _TONEGENERATOR_H_
#define _TONEGENERATOR_H_

#define _USE_MATH_DEFINES
#include <cmath>

class ToneGenerator {
  public:
    ToneGenerator() : sampleRate(0) {}

    virtual double getSample()=0;
    virtual void setFrequency(double frequency)=0;

    void setSampleRate(double sampleRate) { this->sampleRate = sampleRate; }
  protected:
    double sampleRate;
};

#endif
