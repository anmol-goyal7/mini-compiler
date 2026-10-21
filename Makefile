CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Isrc

SRCS = src/main.cpp src/lexer.cpp src/parser.cpp src/codegen.cpp
OBJS = $(SRCS:.cpp=.o)

mycc: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

src/%.o: src/%.cpp src/*.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# compile every program under tests/ and check its exit code or error
test: mycc
	./tests/run.sh

clean:
	rm -f mycc $(OBJS)
	rm -rf tests/out

.PHONY: test clean
