/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_DelayTests_init = false;
#include "DelayTests.h"

static DelayTests suite_DelayTests;

static CxxTest::List Tests_DelayTests = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_DelayTests( "DelayTests.h", 15, "DelayTests", suite_DelayTests, Tests_DelayTests );

static class TestDescription_suite_DelayTests_testPrepareToPlay : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_DelayTests_testPrepareToPlay() : CxxTest::RealTestDescription( Tests_DelayTests, suiteDescription_DelayTests, 33, "testPrepareToPlay" ) {}
 void runTest() { suite_DelayTests.testPrepareToPlay(); }
} testDescription_suite_DelayTests_testPrepareToPlay;

static class TestDescription_suite_DelayTests_testProcessBlock : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_DelayTests_testProcessBlock() : CxxTest::RealTestDescription( Tests_DelayTests, suiteDescription_DelayTests, 38, "testProcessBlock" ) {}
 void runTest() { suite_DelayTests.testProcessBlock(); }
} testDescription_suite_DelayTests_testProcessBlock;

static class TestDescription_suite_DelayTests_testProcessSample : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_DelayTests_testProcessSample() : CxxTest::RealTestDescription( Tests_DelayTests, suiteDescription_DelayTests, 44, "testProcessSample" ) {}
 void runTest() { suite_DelayTests.testProcessSample(); }
} testDescription_suite_DelayTests_testProcessSample;

static class TestDescription_suite_DelayTests_testResizeDelayLine : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_DelayTests_testResizeDelayLine() : CxxTest::RealTestDescription( Tests_DelayTests, suiteDescription_DelayTests, 55, "testResizeDelayLine" ) {}
 void runTest() { suite_DelayTests.testResizeDelayLine(); }
} testDescription_suite_DelayTests_testResizeDelayLine;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
