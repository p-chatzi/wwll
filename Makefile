default: run

run: clean build
	g++ src/*.cpp -o out/magi -Wall -Werror -O0 -lsfml-graphics -lsfml-window -lsfml-system
	./out/magi

build:
	mkdir out

clean:
	rm -rf out