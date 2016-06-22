UNAME    = $(shell uname)
EXE      = baselineReco 
 
VPATH  = .:./interface
vpath %.h ./interface

CSUF   = cc
HSUF   = h
DICTC  = Dict.$(CSUF)
DICTH  = $(patsubst %.$(CSUF),%.h,$(DICTC))

SRCS   = src/argvparser.cc src/DataFormats.cc src/BeamAnaBase.cc src/Utility.cc src/Histogrammer.cc   
OBJS   = $(patsubst %.$(CSUF), %.o, $(SRCS))


LDFLAGS  = -g
SOFLAGS  = -shared 
CXXFLAGS = -I./interface -I./  

CXX       = g++
CXXFLAGS += -g -std=c++11


HDRS_DICT = interface/DataFormats.h interface/LinkDef.h

bin: baselineReco clusterCorrelations 
all: 
	gmake cint 
	gmake bin 
cint: $(DICTC) 

$(DICTC): $(HDRS_DICT)
	@echo "Generating dictionary $(DICTC) and $(DICTH) ..."
	rootcint -f $@ -c $(CXXFLAGS) $^ 
	perl -pi -e 's#interface/##' $(DICTH) 
	perl -pi -e 's/#include <math.h>/#include <math.h>\n#include <map>/'  $(DICTH)
	mv $(DICTC) src/
	mv $(DICTH) interface/

ClusterAnalysis.o : src/ClusterAnalysis.cc
	$(CXX)  $(CXXFLAGS) `root-config --cflags` -o $@ -c $<
	mv $@ ../src/

BaselineAnalysis.o : src/BaselineAnalysis.cc
	$(CXX)  $(CXXFLAGS) `root-config --cflags` -o $@ -c $<
	mv $@ ../src/

clusterCorrelations:   src/clusterCorrelations.cc $(OBJS) src/ClusterAnalysis.o src/Dict.o
	$(CXX) $(CXXFLAGS) `root-config --cflags` $(LDFLAGS) $^ -o $@ $(LIBS) `root-config --libs`

baselineReco:   src/baselineReco.cc $(OBJS) src/BaselineAnalysis.o src/Dict.o
	$(CXX) $(CXXFLAGS) `root-config --cflags` $(LDFLAGS) $^ -o $@ $(LIBS) `root-config --libs`

# Create object files
%.o : %.$(CSUF)
	$(CXX) $(CXXFLAGS) `root-config --cflags` -o $@ -c $<

# makedepend
depend: $(SRCS:.$(CSUF)=.$(CSUF).dep)
	@cat $(notdir $^) > Makefile.dep
	@-rm -f $(notdir $^) $(patsubst %,%.bak,$(notdir $^))
%.dep:
	@touch $(notdir $@)
	rmkdepend -f$(notdir $@) -- $(CXXFLAGS) `root-config --cflags` -- $*
include Makefile.dep

# Clean 
.PHONY   : clean 
clean : 
	@-rm $(OBJS) $(EXE) interface/$(DICTH) src/$(DICTC) src/*.o  

