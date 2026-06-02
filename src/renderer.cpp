#include "renderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Game.h"

const int TILE_SIZE=100;
const int TILE_PADDING=10;
const int BOARD_OFFSET=20;

Renderer::Renderer(int windowW,int windowH){
    SDL_Init(SDL_INIT_VIDEO);
    window=SDL_CreateWindow("Game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,windowW,windowH,0);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    TTF_Init();
    font=TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 24.0)
}

Renderer::~Renderer(){
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Color Renderer::tileColor(int value){
    switch(value){
        case 0: return {192,192,192,255};
        case 2: return {245,222,179,255};
        case 4: return {244,164,96,255};
        case 8: return {205,133,63,255};
        case 16: return {255,140,0,255};
        case 32: return {255,69,0,255};
        case 64: return {255,99,71,255};
        case 128: return {255,215,0,255};
        case 256: return {218,165,32,255};
        case 512: return {184,134,11,255};
        case 1024: return {210,105,30,255};
        case 2048: return {220,20,60,255};
        case default: return {128,128,128,255};
    }
}
void Renderer::drawTile(int value, int x, int y){

    SDL_Color color =tileColor(value);
    SDL_Rect rect= {x,y,TILE_SIZE,TILE_SIZE};
    SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a);
    SDL_RenderFillRect(renderer,&rect);
    if(value !=0){
        std::string string_value= std::to_string(value);
        SDL_Color textColor={255,255,255,255};
        SDL_Surface* surface =TTF_RenderText_Solid(font, string_value,textColor);
        SDL_Texture* texture= SDL_CreateTextureFromSurface(renderer,surface);
        SDL_RenderCopy(render,texture,nullptr,&rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

}
void Renderer::drawBoard(const int* board){
    for(int i=0;i<4;++i){
        for(int j=0;j<4;++j){
            int x= BOARD_OFFSET+ j*(TILE_SIZE+TILE_PADDING);
            int y= BOARD_OFFSET+ i *(TILE_SIZE+TILE_PADDING);
            drawTile(board[i*4+j],x,y);
        }
    }
}

void Renderer::drawScore(int score){
    std::string score_string= "Score:" + std::to_string(score);
    SDL_Color textColor={255,255,255,255};
    SDL_Rect rect={10,620,200,40};
    SDL_Surface* surface= TTF_RenderText_Solid(font,score_string.c_str(),textColor);
    SDL_Texture* texture=SDL_CreateTextureFromSurface(renderer,surface);
    SDL_RenderCopy(renderer,texture,nullptr,&rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Renderer::drawGameOver(){

    std::string text= "Game Over! Thanks for playing.";
    SDL_Color textColor={255,255,255,255};
    SDL_Rect rect={10,0,200,40};
    SDL_Surface* surface=TTF_RenderText_Solid(font,text.c_str(),textColor);
    SDL_Texture* texture= SDL_CreateTextureFromSurface(renderer,surface);
    SDL_RenderCopy(renderer,texture,nullptr,&rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

}
void Renderer::draw(const Game& game){
    SDL_SetRenderDrawColor(renderer,135,206,235,235);
    drawBoard(game.getBoard);
    drawScore(game.getScore);
    if(game.hasWon==2048 || game.isOver()) drawGameOver()
}

void Renderer::present(){
    SDL_RendererPresent(renderer);

}
