CXXTEST_HOME = cxxtest-4.4
CXXTEST_GEN = $(CXXTEST_HOME)/bin/cxxtestgen
CXXTEST_INCLUDE = $(CXXTEST_HOME)
CXXTEST_INCLUDE = $(CXXTEST_HOME)
JUCE_DIR = /home/csun/JUCE/modules

.PHONY: all clean

all: runner

FilterTests.cpp: FilterTests.h
	$(CXXTEST_GEN) --error-printer $< -o $@

DelayTests.cpp: DelayTests.h
	$(CXXTEST_GEN) --error-printer $< -o $@
	
GeneratorTests.cpp: GeneratorTests.h
	$(CXXTEST_GEN) --error-printer $< -o $@

runner: FilterTests.cpp FilterTests.h GeneratorTests.cpp GeneratorTests.h
	g++ -std=gnu++11 -I$(JUCE_DIR) -I$(CXXTEST_INCLUDE) $< -o $@

clean:
	rm -f runner DelayTests.cpp FilterTests.cpp GeneratorTests.cpp
