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

void handle_input(SDL_Event& event){

        if(event.type==SDL_KEYDOWN){
            switch (event.key.keysym.sym)
            {
            case SDLK_UP: 
            if(direction!=DOWN)direction=UP; break;
            
            case SDLK_DOWN: 
            if(direction!=UP)direction=DOWN; break;

            case SDLK_RIGHT: 
            if(direction!=RIGHT)direction=LEFT; break;

            case SDLK_LEFT: 
            if(direction!=LEFT)direction=RIGHT; break;
            }
        }
}

void render(){
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer,255,255,255,255);

    for(int i=0;i<snakeLength;i++){
        SDL_Rect snake_rect={foodX*Tile_Size,foodY*Tile_Size,Tile_Size,Tile_Size};
        SDL_RenderFillRect(renderer,&snake_rect);
    }

    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_Rect foodRect= {foodX*Tile_Size,foodY*Tile_Size,Tile_Size,Tile_Size};
    SDL_RenderFillRect(renderer, &foodRect);
    SDL_RenderPresent(renderer);
}

int main(int argc, char* args[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    window=SDL_CreateWindow("Snake Game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
    Screen_Width,Screen_Hieght, SDL_WINDOW_SHOWN);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    initialize_game();
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

