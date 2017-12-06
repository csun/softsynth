CXXTEST_HOME = cxxtest-4.4
CXXTEST_GEN = $(CXXTEST_HOME)\bin\cxxtestgen
CXXTEST_INCLUDE = $(CXXTEST_HOME)

.PHONY: all clean

all: runner

FilterTests.cpp: FilterTests.h
	$(CXXTEST_GEN) --error-printer $< -o $@

DelayTests.cpp: DelayTests.h
	$(CXXTEST_GEN) --error-printer $< -o $@
	
GeneratorTests.cpp: GeneratorTests.h
	$(CXXTEST_GEN) --error-printer $< -o $@

runner: DelayTests.cpp DelayTests.h FilterTests.cpp FilterTests.h GeneratorTests.cpp GeneratorTests.h
	g++ $< -I$(CXXTEST_INCLUDE) -o $@

clean:
	rm -f runner DelayTests.cpp FilterTests.cpp GeneratorTests.cpp
