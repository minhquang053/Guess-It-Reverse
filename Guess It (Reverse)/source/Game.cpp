#include "Game.h"

#define BIGGER 1
#define SMALLER 2
#define CORRECT 3

int clicked = -1;

void Game::LoadNum()
{
    SDL_Surface* tsurface = TTF_RenderText_Solid(this->font, std::to_string(currentNum).c_str(), {0,0,0});
    this->text = SDL_CreateTextureFromSurface(this->renderer, tsurface);
    SDL_QueryTexture(this->text, nullptr, nullptr, &(this->desText.w), &(this->desText.h));
    desText.x = 300; desText.y = 110;
    SDL_FreeSurface(tsurface);
}

Game::Game()
{
    InitSDL(this->window, this->renderer);
    this->isRunning = true;

    this->font = TTF_OpenFont("assets/right.ttf", 70);

    this->background = new GameObject(this->renderer, "assets/bg.png");
    this->background->updatePosition(0,0,0.5);
    this->surround = new GameObject(this->renderer, "assets/surround.png");
    this->board = new GameObject(this->renderer, "assets/board.png");
    this->board->updatePosition(125, 80, 0.75);
    this->again = new GameObject(this->renderer, "assets/again.png");
    this->again->updatePosition(280,400,1); // waiting to be changed
    this->okay = new GameObject(this->renderer, "assets/okay.png");
    this->okay->updatePosition(600, 500, 0.5);
    this->bigger = new GameObject(this->renderer, "assets/bigger.png");
    this->bigger->updatePosition(200, 200, 0.4);
    this->smaller = new GameObject(this->renderer, "assets/smaller.png");
    this->smaller->updatePosition(200, 250, 0.4);
    this->correct = new GameObject(this->renderer, "assets/correct.png");
    this->correct->updatePosition(180, 300, 0.4);

    LoadNum();

    std::cout << "Start game\n";
}

Game::~Game()
{
    QuitSDL(this->window, this->renderer);
    std::cout << "End game\n";
}

void Game::render()
{
    SDL_RenderClear(renderer);
    this->background->objRender(this->renderer);
    okay->objRender(this->renderer);
    board->objRender(this->renderer);
    this->bigger->objRender(this->renderer);
    this->smaller->objRender(this->renderer);
    this->correct->objRender(this->renderer);
    if (clicked >= 0) this->surround->objRender(this->renderer);
    if (this->currentNum > 0) SDL_RenderCopy(this->renderer, text, nullptr, &desText);
    SDL_RenderPresent(this->renderer);

    SDL_Delay(20);
}

void Game::input()
{
    while (SDL_WaitEvent(&(this->event)))
    {
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            int xm = event.button.x, ym = event.button.y;

            if (this->smaller->checkClick(xm, ym)) {
                clicked = SMALLER;
                goto NEXT;
            } else if (this->bigger->checkClick(xm, ym)) {
                clicked = BIGGER;
                goto NEXT;
            } else if (this->correct->checkClick(xm, ym)) {
                clicked = CORRECT;
                goto NEXT;
            }
            if (this->okay->checkClick(xm, ym)) {
                this->submit = true;
                goto NEXT;
            }
        }
        else if (event.type == SDL_QUIT)
        {
            this->isRunning = false;
            this->quit = true;
            break;
        }
        SDL_FlushEvents(SDL_USEREVENT, SDL_LASTEVENT);
    }
NEXT:
    {
    }
}

void Game::update()
{
    // game rule here


    if (clicked > -1) this->surround->updatePosition(200, 200+(clicked-1)*50-10, 0.04);

    if (this->submit)
    {
        switch (clicked) {
            case SMALLER:
                lastNum = currentNum;
                break;
            case BIGGER:
                firstNum = currentNum;
                break;
            case CORRECT:
                this->isRunning = false;
                this->currentNum = -1;
                break;
            default:
                break;
        }
        currentNum = static_cast<int>((firstNum + lastNum)/2);
        this->submit = false;
    }

    LoadNum();

    //
}

void Game::render(const char *random)
{
    SDL_RenderClear(renderer);
    this->background->objRender(this->renderer);
    this->again->objRender(this->renderer);

    SDL_RenderPresent(this->renderer);
    SDL_Delay(20);
}

void Game::input(const char *random)
{
    while(SDL_WaitEvent(&(this->event)))
    {
        int xm = event.button.x, ym = event.button.y;
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            if (this->again->checkClick(xm, ym))
            {
                this->setReplay();
                this->isRunning = true;
            }
            break;
        }
        else if (event.type == SDL_QUIT)
        {
            this->quit = true;
            break;
        }
    }
}

void Game::update(const char *random)
{
    this->firstNum = 0;
    this->lastNum = 1000;
    this->currentNum = 500;
    this->surround->updatePosition(0,0,0);
    LoadNum();
}
