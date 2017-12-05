//
//  FilterTests.h
//  SoftSynth
//
//  Created by Cole Vick on 12/3/17.
//

#ifndef FilterTests_h
#define FilterTests_h

#include <Source/FilterProcessor.h>
#include <cxxtest/TestSuite.h>

class FilterTests : public CxxTestSuite.h {
    FilterProcessor filter;
    AudioSampleBuffer aBuffer;
    MidiBuffer mBuffer;
    
public:
    void setUp() {
        filter = new FilterProcessor();
    }
    
    void tearDown() {
        delete filter;
    }
    
    void testPrepareToPlay() {
        filter.prepareToPlay(2.0f, 3);
        TS_ASSERT_EQUALS(filter.sampleRate, 2.0f);
    }
    
    void testProcessBlock() {
        filter.testProcessBlock(aBuffer, mBuffer);
        
        TS_ASSERT_EQUALS(filter.delayLine.empty(), true);
    }
    
    void testProcessSample() {
        
    }
    
    void testUpdateCoefficients() {
        
    }
    
}

#endif /* FilterTests_h */
