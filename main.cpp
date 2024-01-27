#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
bool gameisrunning = true;
const int screen_width = 800;
const int screen_height = 600;
const int grid_size = 20;
const int font_size = 24;

class Snake {
public:
    Snake();
    void handleMenuInput(SDL_Event &event);
    void handleGameInput(SDL_Event &event);
    void update();
    void render(SDL_Renderer *renderer);
    void renderMenu(SDL_Renderer *renderer);
    void renderExitScreen(SDL_Renderer *renderer);
    void loadBackground(SDL_Renderer *renderer); 
    bool checkCollision();
    void reset();
    void generateFood();
    void generateBonusFood();
    void resetBonusFoodTimer();
    int loadHighScore();
    void saveHighScore();

    enum GamePhase {
        MENU,
        GAMEPLAY,
        COLLISION,
        EXIT,
    } phase;

private:
    std::vector<std::pair<int, int>> body;
    std::pair<int, int> food;
    std::pair<int, int> bonusFood;
    int direction;
    int bonusFoodTimer =-1;
    int score=0;
    int highScore;


    TTF_Font *font;
    SDL_Color textColor;
    SDL_Texture *backgroundTexture;
    const char *highScoreFileName = "highscore.txt";

};

Snake::Snake() {

    reset();

    phase = MENU;
    font = TTF_OpenFont("safu.otf", font_size);
    textColor = {255, 255, 255, 255};
    backgroundTexture = nullptr;
    highScore = loadHighScore();
}

void Snake::handleMenuInput(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_RETURN:  
                if (phase == MENU) {
                    phase = GAMEPLAY;
                    reset();
                }
                break;
            case SDLK_ESCAPE:  
                if (phase != EXIT) {
                    phase = EXIT;
                   
                }
                break;
        }
    }
}


void Snake::handleGameInput(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                if (direction != 2)
                    direction = 0;
                break;
            case SDLK_RIGHT:
                if (direction != 3)
                    direction = 1;
                break;
            case SDLK_DOWN:
                if (direction != 0)
                    direction = 2;
                break;
            case SDLK_LEFT:
                if (direction != 1)
                    direction = 3;
                break;
        }
    }
}

void Snake::update() {
    std::pair<int, int> head = body.front();

    switch (direction) {
        case 0:  // up
            head.second -= 1;
            break;
        case 1:  // right
            head.first += 1;
            break;
        case 2:  // down
            head.second += 1;
            break;
        case 3:  // left
            head.first -= 1;
            break;
    }
    if (head.first < 0) {
        head.first = screen_width / grid_size - 1;
    } else if (head.first >= screen_width / grid_size) {
        head.first = 0;
    }

    if (head.second < 0) {
        head.second = screen_height / grid_size - 1;
    } else if (head.second >= screen_height / grid_size) {
        head.second = 0;
    }


    body.insert(body.begin(), head);

    if (checkCollision()) {
       
        phase = COLLISION;
        if (score > highScore) {
        highScore = score;
        saveHighScore();  
    }
    } else {
        if (head == food) {
            generateFood();
            score += 5;
            resetBonusFoodTimer();
        } else {
            if (body.size() > 1) {
                body.pop_back();
            }
        }

        if (head == bonusFood) {
            score += 10;
            bonusFood = {1234, 1234};
            resetBonusFoodTimer();
        }
    }

    if (bonusFoodTimer > 0) {
        bonusFoodTimer--;
        if (bonusFoodTimer == 0) {
            bonusFood = {1234, 1234};
        }
    }

    
}

void Snake::render(SDL_Renderer *renderer) {

     loadBackground(renderer);

    SDL_Rect foodRect = {food.first * grid_size, food.second * grid_size, grid_size, grid_size};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &foodRect);

    if (bonusFoodTimer > 0) {
        SDL_Rect bonusFoodRect = {bonusFood.first * grid_size, bonusFood.second * grid_size, grid_size, grid_size};
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &bonusFoodRect);
    }

    for (const auto &segment : body) {
        SDL_Rect rectsnake = {segment.first * grid_size, segment.second * grid_size, grid_size, grid_size};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rectsnake);
    }

    std::pair<int, int> head = body.front();

    SDL_Rect headRect = {head.first * grid_size, head.second * grid_size, grid_size, grid_size};
    SDL_SetRenderDrawColor(renderer, 255, 155, 55, 255);
    SDL_RenderFillRect(renderer, &headRect);

    std::string scoreText = "Score: " + std::to_string(score);
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect textRect = {10, 10, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

     std::string highScoreText = "High Score: " + std::to_string(highScore);
    SDL_Surface *highScoreSurface = TTF_RenderText_Solid(font, highScoreText.c_str(), textColor);
    SDL_Texture *highScoreTexture = SDL_CreateTextureFromSurface(renderer, highScoreSurface);

    SDL_Rect highScoreRect = {10, 40, highScoreSurface->w, highScoreSurface->h};
    SDL_RenderCopy(renderer, highScoreTexture, nullptr, &highScoreRect);


    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void Snake::renderMenu(SDL_Renderer *renderer) {
    std::string menuText = "Press ENTER to start\n ESC to exit";
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, menuText.c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect textRect = {screen_width / 2 - textSurface->w / 2, screen_height / 2 - textSurface->h / 2,
                         textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}


void Snake::renderExitScreen(SDL_Renderer *renderer) {
    std::string exitText = "Game Over! Your Score: " + std::to_string(score);
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, exitText.c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect textRect = {screen_width / 2 - textSurface->w / 2, screen_height / 2 - textSurface->h / 2,
                         textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
   
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

int Snake::loadHighScore() {
    std::ifstream file(highScoreFileName);

    if (!file.is_open()) {
        std::cerr << "Error opening high score file. Defaulting to 0.\n";
        return 0;
    }

    int score;
    file >> score;

    file.close();

    return score;
}

void Snake::saveHighScore() {
    std::ofstream file(highScoreFileName);

    if (!file.is_open()) {
        std::cerr << "Error opening high score file for writing.\n";
        return;
    }

    file << highScore;

    file.close();
}


void Snake::loadBackground(SDL_Renderer *renderer) {
    // Load background image
    SDL_Surface *backgroundSurface = IMG_Load("background.jpg"); // Replace with your image file
    

  
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
}
bool Snake::checkCollision() {
    std::pair<int, int> head = body.front();

  

    if (head.first < 0 || head.first >= screen_width / grid_size ||
        head.second < 0 || head.second >= screen_height / grid_size) {
        return true;
    }

    for (auto it = body.begin() + 1; it != body.end(); ++it) {
        if (head == *it) {
            return true;
        }
    }

    return false;
}

void Snake::reset() {
    body.clear();
    body.push_back({screen_width / (2 * grid_size), screen_height / (2 * grid_size)});
    direction = 1;
    generateFood();
}

void Snake::generateFood() {
    food = {rand() % (screen_width / grid_size), rand() % (screen_height / grid_size)};
}

void Snake::generateBonusFood() {
    bonusFood = {rand() % (screen_width / grid_size), rand() % (screen_height / grid_size)};
    bonusFoodTimer = 40;
}

void Snake::resetBonusFoodTimer() {
    if (body.size() > 1 && (body.size() - 1) % 4 == 0) {
        generateBonusFood();
    }
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          screen_width, screen_height, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Init() ;
      

    Snake snake;

    SDL_Event event;

    srand(static_cast<unsigned>(time(NULL)));

    while (gameisrunning) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                gameisrunning = false;
            } else {
                if (snake.phase == Snake::MENU) {
                    snake.handleMenuInput(event);
                } else {
                    snake.handleGameInput(event);
                }
            }
        }

        snake.update();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        if (snake.phase == Snake::MENU) {
            snake.renderMenu(renderer);
        } else if (snake.phase == Snake::GAMEPLAY) {
            snake.render(renderer);
        } else if (snake.phase == Snake::COLLISION) {
            // Render exit screen with final score
            snake.renderExitScreen(renderer);
           
        }


        SDL_RenderPresent(renderer);

        SDL_Delay(100);
    }
    

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
