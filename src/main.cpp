#include <iostream>
#include "renderer.h"
#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

const int SCREEN_WIDTH=600;
const int SCREEN_HEIGHT=700;

int main(){
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        std::cerr<<"SDL initialization failed!"<<SDL_GetError()<<std::endl;
        return -1;
    }

    Renderer game_renderer(SCREEN_WIDTH,SCREEN_HEIGHT);
    Game  game;
    bool isRunning=true;
    SDL_Event event;

    while(isRunning){

        while(SDL_PollEvent(&event)){
            if(event.type ==SDL_QUIT) isRunning=false;
            if(event.type ==SDL_KEYDOWN){
                if(game.isOver() || game.hasWon()){
                    if(event.key.keysym.sym ==SDLK_r) game.reset();
                }else{
                    switch(event.key.keysym.sym){
                        case SDLK_LEFT: game.move(Direction::LEFT); break;
                        case SDLK_RIGHT: game.move(Direction::RIGHT); break;
                        case SDLK_UP: game.move(Direction::UP); break;
                        case SDLK_DOWN: game.move(Direction::DOWN); break;
                        case SDLK_r: game.reset(); break;
                    }
                }
            }
        }
        game_renderer.draw(game);
        game_renderer.present();

        SDL_Delay(16);
    }
    return 0;
}
