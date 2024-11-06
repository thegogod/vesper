clean:
	rm -rf bin

build: clean
	mkdir bin
	clang++ -g -std=c++20 src/*.cpp -o bin/main

run: build
	./bin/main