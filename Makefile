all: treematch

CXX ?= clang++
OBJS := src/Node.o src/NodeBase.o src/WildcardNode.o src/TreeMatch.o \
				src/DecisionTreeNode.o

CPPFLAGS += -Iinclude

treematch: $(OBJS)
	$(CXX) --std=c++11 -o treematch $(OBJS)

-include $(OBJS:.o=.d)

%.o : %.C
	$(CXX) -std=c++11 -c $(CXXFLAGS) $(CPPFLAGS) $*.C -o $@
	$(CXX) -std=c++11 -MM $(CXXFLAGS) $(CPPFLAGS) $*.C > $*.d

clean:
	rm treematch $(OBJS) src/*.d
