all: build run

run: 
	./a.out

build: sokoban_game.cpp
	g++ sokoban_game.cpp -lGL -lGLU -lglut

clean:
	rm ./a.out
