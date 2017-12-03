//
//  DelayTests.h
//  SoftSynth
//
//  Created by Cole Vick on 12/3/17.
//

#ifndef DelayTests_h
#define DelayTests_h

#include <Source/FilterProcessor.h>
#include <cxxtest/TestSuite.h>

class DelayTests : public CxxTestSuite.h {
    DelayProcessor delay;
    
public:
    void setUp() {
        delay = new DelayProcessor();
    }
    
    void tearDown() {
        delete delay;
    }
    
    void testProcessBlock() {
        
    }
    
    void testProcessSample() {
        
    }
    
    void testResizeDelayLine() {
        
    }
    
#endif /* DelayTests_h */
