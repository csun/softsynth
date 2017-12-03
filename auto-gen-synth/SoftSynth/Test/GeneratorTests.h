//
//  GeneratorTests.h
//  SoftSynth
//
//  Created by Cole Vick on 12/3/17.
//

#ifndef GeneratorTests_h
#define GeneratorTests_h
#include <Source/ToneGenerator.h>
#include <Source/SineToneGenerator.h>
#include <Source/SawToneGenerator.h>
#include <Source/SquareToneGenerator.h>
#include <cxxtest/TestSuite.h>

class GeneratorTests : public CxxTestSuite.h {
    SineToneGenerator sine;
    SquareToneGenerator square;
    SawToneGenerator sine;
    
public:
    void setUp() {
        sine = new SineToneGenerator();
        square = new SquareToneGenerator();
        saw = new SawToneGenerator();
    }
    
    void tearDown() {
        delete sine;
        delete square;
        delete saw;
    }
    

    void testSineGetSample() {
        
    }
    
    void testSquareGetSample() {
        
    }
    
    void testSawGetSample() {
        
    }
    
    void testSineSetFrequency() {
        
    }
    
    void testSquareSetFrequency() {
        
    }
    
    void testSawSetFrequency() {
        
    }
    
   
}

#endif /* GeneratorTests_h */
