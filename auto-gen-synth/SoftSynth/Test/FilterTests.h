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
    
public:
    void setUp() {
        filter = new FilterProcessor();
    }
    
    void tearDown() {
        delete filter;
    }
    
    void testProcessBlock() {
        
    }
    
    void testProcessSample() {
        
    }
    
    void testUpdateCoefficients() {
        
    }
    
}

#endif /* FilterTests_h */
