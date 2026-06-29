CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Isrc

mycc: src/main.cpp src/lexer.cpp src/parser.cpp src/codegen.cpp src/token.h src/ast.h
	$(CXX) $(CXXFLAGS) src/main.cpp -o mycc

# compile a .c test file all the way to an executable
test: mycc
	./mycc tests/test.c > tests/test.s
	$(CXX) tests/test.s -o tests/test_bin
	./tests/test_bin; echo "exit code: $$?"

clean:
	rm -f mycc tests/test.s tests/test_bin

.PHONY: test clean
