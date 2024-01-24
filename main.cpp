#include<SDL2/SDL.h>
#include<iostream>

const int Screen_Width=840;
const int Screen_Hieght=680;
const int Tile_Size=20;
const int Board_Width= Screen_Width/Tile_Size;
const int Board_Height=Screen_Hieght/Tile_Size;

SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;

int snakeX[1000];
int snakeY[1000];
int snakeLength=1;
int foodX,foodY;

enum Direction { UP, DOWN, LEFT, RIGHT };
Direction direction = RIGHT; 

void generate_food(){
    foodX=rand()%Board_Width;
    foodY=rand()%Board_Height;
}

void initialize_game(){
    snakeX[0]=Tile_Size;
    snakeY[0]=Tile_Size;
    snakeLength=2;
    direction= RIGHT;
    generate_food();
}

int main(int argc, char* args[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    window=SDL_CreateWindow("Snake Game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
    Screen_Width,Screen_Hieght, SDL_WINDOW_SHOWN);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    bool game_running= true;
    SDL_Event event;
    while(game_running){
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                game_running==false;
                
            }
        }
    }

}

