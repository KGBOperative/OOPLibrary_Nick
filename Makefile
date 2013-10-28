CXX=g++
LD=ld
CFLAGS=-c -g -MMD
LDFLAGS=

MAIN=Main.cpp
SOURCES=Library.cpp Asset.cpp Book.cpp Periodical.cpp Member.cpp Date.cpp $(MAIN) 
OBJECTS=$(SOURCES:.cpp=.o)
DEPS=$(OBJECTS:.o=.d)
EXECUTABLE=$(MAIN:.cpp=.out)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

-include $(DEPS)

.cpp.o:
	$(CXX) $(CFLAGS) -MF $(patsubst %.o,%.d,$@) $< -o $@

clean: 
	rm -rf $(OBJECTS) $(DEPS) $(EXECUTABLE)

test: all
	./Main.out
