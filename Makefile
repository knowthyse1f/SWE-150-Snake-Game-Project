all:
	 g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
	 ./main


	 g++ -I src/include -L src/lib -o main test.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
	 ./main