default: run

run: clean build
	g++ src/*.cpp -o out/magi -Wall -Werror -O0
	./out/magi

build:
	mkdir out

clean:
	rm -rf out