INCLUDES = ../include
STD      = c++17
CFLAGS   = $(if $(DEBUG),-g2 -O0 -DDEBUG,-O2) $(INCLUDES:%=-I%)
CXXFLAGS = -std=$(STD)
WFLAGS   = -pedantic -pedantic-errors -Wall -Wextra -Werror -Wconversion -Wcast-align -Wcast-qual -Wctor-dtor-privacy \
           -Wdisabled-optimization -Wmissing-declarations -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual \
           -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wswitch-default -Wundef -Weffc++ -Wfloat-equal

LIBS     = gtest
INSTALL  = $(if $(VERBOSE),,@)cp -r
BUILDDIR = build
LDFLAGS  = -Wl,--gc-sections

MAKEFLAGS+= --no-builtin-rules
SOURCES  := $(shell ls -1 *.cxx)
OBJECTS  = $(SOURCES:%.cxx=$(BUILDDIR:%=%/)%.o)

all: $(BUILDDIR:%=%/)nameof_test

run-tests: $(BUILDDIR:%=%/)nameof_test
	$(BUILDDIR:%=%/)nameof_test

$(BUILDDIR:%=%/)nameof_test: $(OBJECTS)
	$(CXX) $(CFLAGS) $(CXXFLAGS) $(LDFLAGS) -MMD -MP -MF$(@:.o=.d) -MT$@ -o $@ $^ $(LIBS:%=-l%)


$(BUILDDIR:%=%/)%.o: %.cxx | $(BUILDDIR)
	$(CXX) $(CFLAGS) $(CXXFLAGS) $(WFLAGS) -MMD -MP -MF$(@:.o=.d) -MT$@ -o $@ -c $<

$(BUILDDIR):
	@mkdir -p $@

clean:
	rm -rf $(BUILDDIR)
	