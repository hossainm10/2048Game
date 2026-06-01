#pragma once
#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
class Renderer{
    public:
        Renderer(int windowW, int windowH);
        ~Renderer();

        void draw(const Game& game);
        void drawBoard(const int board[4][4]);
        void drawTile(int value, int x, int y);
        void drawScore(int score);
        void drawGameOver();
        void present();
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        TTF_Font* font;
        SDL_Color tileColor(int value);
};
