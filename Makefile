all: build run

run: 
	./a.out

build: sokoban.cpp
	g++ sokoban.cpp -lGL -lGLU -lglut

clean:
	rm ./a.out
