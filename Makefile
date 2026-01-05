CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -pedantic

BIN=bin

all: $(BIN)

$(BIN):
	mkdir -p $(BIN)

clean:
	rm -rf *.o *.gch $(BIN)

bin/%: %.cpp
	mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) -o $@ $<

