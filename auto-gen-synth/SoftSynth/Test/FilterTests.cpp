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
bool suite_FilterTests_init = false;
#include "FilterTests.h"

static FilterTests suite_FilterTests;

static CxxTest::List Tests_FilterTests = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_FilterTests( "FilterTests.h", 14, "FilterTests", suite_FilterTests, Tests_FilterTests );

static class TestDescription_suite_FilterTests_testPrepareToPlay : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FilterTests_testPrepareToPlay() : CxxTest::RealTestDescription( Tests_FilterTests, suiteDescription_FilterTests, 28, "testPrepareToPlay" ) {}
 void runTest() { suite_FilterTests.testPrepareToPlay(); }
} testDescription_suite_FilterTests_testPrepareToPlay;

static class TestDescription_suite_FilterTests_testProcessBlock : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FilterTests_testProcessBlock() : CxxTest::RealTestDescription( Tests_FilterTests, suiteDescription_FilterTests, 33, "testProcessBlock" ) {}
 void runTest() { suite_FilterTests.testProcessBlock(); }
} testDescription_suite_FilterTests_testProcessBlock;

static class TestDescription_suite_FilterTests_testProcessSample : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FilterTests_testProcessSample() : CxxTest::RealTestDescription( Tests_FilterTests, suiteDescription_FilterTests, 39, "testProcessSample" ) {}
 void runTest() { suite_FilterTests.testProcessSample(); }
} testDescription_suite_FilterTests_testProcessSample;

static class TestDescription_suite_FilterTests_testUpdateCoefficients : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FilterTests_testUpdateCoefficients() : CxxTest::RealTestDescription( Tests_FilterTests, suiteDescription_FilterTests, 43, "testUpdateCoefficients" ) {}
 void runTest() { suite_FilterTests.testUpdateCoefficients(); }
} testDescription_suite_FilterTests_testUpdateCoefficients;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
