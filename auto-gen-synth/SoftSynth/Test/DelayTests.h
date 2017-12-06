//
//  DelayTests.h
//  SoftSynth
//
//  Created by Cole Vick on 12/3/17.
//

#ifndef DelayTests_h
#define DelayTests_h

#include "../Source/DelayProcessor.h"
#include "../Source/FilterProcessor.h"
#include <cxxtest/TestSuite.h>

class DelayTests : public CxxTest::TestSuite {
    DelayProcessor delay;
    AudioSampleBuffer aBuffer;
    MidiBuffer mBuffer;
    
public:
    void setUp() {
        delay = new DelayProcessor();
        aBuffer = new AudioSampleBuffer();
        mBuffer = new MidiBuffer();
    }
    
    void tearDown() {
        delete delay;
        delete aBuffer;
        delete mBuffer;
    }
    
    void testPrepareToPlay() {
        delay.prepareToPlay(2.0f, 3);
        TS_ASSERT_EQUALS(delay.sampleRate, 2.0f);
    }
    
    void testProcessBlock() {
        delay.testProcessBlock(aBuffer, mBuffer);
        
        TS_ASSERT_EQUALS(delay.delayLine.empty(), true);
    }
    
    void testProcessSample() {
        std::deque<float> delayL (1, 0.75f);
        delay.delayLine = delayL;
        
        float samp = 0.5f;
        
        delay.processSample(samp);
        
        TS_ASSERT_EQUALS(samp, 0.625f);
    }
    
    void testResizeDelayLine() {
        
        delay.resizeDelayLine();
        float delayFloat = delay.delayLine.pop_front();
        TS_ASSERT_EQUALS(delayFloat, 0.0f);
        
    }
    
#endif /* DelayTests_h */
