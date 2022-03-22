#include "GameObject.h"
#include <ctime>
#include <cstdlib>
#include <string>

#ifndef GAME_H
#define GAME_H

class Game
{
public:
    Game();
    ~Game();
    bool is_running() {
        return this->isRunning;
    }
    bool getReplay() {
        return this->replay;
    }
    void setReplay() {
        this->replay = true;
    }
    bool getQuit() {
        return this->quit;
    }

    void LoadNum();
    void render();
    void render(const char *random);
    void update();
    void update(const char *random);
    void input();
    void input(const char *randon);
private:
    bool isRunning = false, replay = false, quit = false, submit = false;
    int firstNum {0}, lastNum {1000}, currentNum {500};
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;

    TTF_Font* font;
    SDL_Rect desText {0,0,0,0};
    SDL_Texture* text;

    GameObject *surround, *board, *again, *background, *okay, *bigger, *smaller, *correct;
};

#endif /* end of include guard: GAME_H */
