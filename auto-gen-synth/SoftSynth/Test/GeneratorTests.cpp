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
bool suite_GeneratorTests_init = false;
#include "GeneratorTests.h"

static GeneratorTests suite_GeneratorTests;

static CxxTest::List Tests_GeneratorTests = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_GeneratorTests( "GeneratorTests.h", 16, "GeneratorTests", suite_GeneratorTests, Tests_GeneratorTests );

static class TestDescription_suite_GeneratorTests_testSineGetSample : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeneratorTests_testSineGetSample() : CxxTest::RealTestDescription( Tests_GeneratorTests, suiteDescription_GeneratorTests, 35, "testSineGetSample" ) {}
 void runTest() { suite_GeneratorTests.testSineGetSample(); }
} testDescription_suite_GeneratorTests_testSineGetSample;

static class TestDescription_suite_GeneratorTests_testSquareGetSample : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeneratorTests_testSquareGetSample() : CxxTest::RealTestDescription( Tests_GeneratorTests, suiteDescription_GeneratorTests, 39, "testSquareGetSample" ) {}
 void runTest() { suite_GeneratorTests.testSquareGetSample(); }
} testDescription_suite_GeneratorTests_testSquareGetSample;

static class TestDescription_suite_GeneratorTests_testSawGetSample : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeneratorTests_testSawGetSample() : CxxTest::RealTestDescription( Tests_GeneratorTests, suiteDescription_GeneratorTests, 43, "testSawGetSample" ) {}
 void runTest() { suite_GeneratorTests.testSawGetSample(); }
} testDescription_suite_GeneratorTests_testSawGetSample;

static class TestDescription_suite_GeneratorTests_testSineSetFrequency : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeneratorTests_testSineSetFrequency() : CxxTest::RealTestDescription( Tests_GeneratorTests, suiteDescription_GeneratorTests, 47, "testSineSetFrequency" ) {}
 void runTest() { suite_GeneratorTests.testSineSetFrequency(); }
} testDescription_suite_GeneratorTests_testSineSetFrequency;

static class TestDescription_suite_GeneratorTests_testSquareSetFrequency : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeneratorTests_testSquareSetFrequency() : CxxTest::RealTestDescription( Tests_GeneratorTests, suiteDescription_GeneratorTests, 51, "testSquareSetFrequency" ) {}
 void runTest() { suite_GeneratorTests.testSquareSetFrequency(); }
} testDescription_suite_GeneratorTests_testSquareSetFrequency;

static class TestDescription_suite_GeneratorTests_testSawSetFrequency : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeneratorTests_testSawSetFrequency() : CxxTest::RealTestDescription( Tests_GeneratorTests, suiteDescription_GeneratorTests, 55, "testSawSetFrequency" ) {}
 void runTest() { suite_GeneratorTests.testSawSetFrequency(); }
} testDescription_suite_GeneratorTests_testSawSetFrequency;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
