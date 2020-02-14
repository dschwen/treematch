all: treematch

CXX ?= clang++
OBJS := Node.o NodeBase.o WildcardNode.o TreeMatch.o

treematch: $(OBJS)
	$(CXX) --std=c++11 -o treematch $(OBJS)

-include $(OBJS:.o=.d)

%.o : %.C
	$(CXX) -std=c++11 -c $(CXXFLAGS) $(CPPFLAGS) $*.C -o $@
	$(CXX) -std=c++11 -MM $(CXXFLAGS) $(CPPFLAGS) $*.C > $*.d

clean:
	rm treematch $(OBJS) *.d
