all:
	 g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image


	  g++ -I src/include -L src/lib -o main manger.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image

	  g++ -I src/include -L src/lib -o main menu.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image

g++ -I src/include -L src/lib -o main test.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image	  



g++ -I src/include -L src/lib -o main main.cpp snake.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image



g++ -I src/include -L src/lib -o main main.cpp game.cpp snake.cpp controller.cpp player.cpp renderer.cpp -lmingw32 -lSDL2main -lSDL2