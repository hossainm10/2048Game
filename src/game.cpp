#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iterator>
#include <vector>
#include <algorithm>

void Game::spawnTile(){
    std::vector<std::pair<int,int>> empty_;
    for (int i=0;i<4;++i){
        for(int j=0;j<4;++j){
            if(board[i][j]==0) empty_.push_back({i,j});
        }
    }
    if(empty_.empty()) return;
    auto [row,col]=empty_[rand() % empty_.size()];
    int value= (rand() %10==0) ? 4:2;
    board[row][col]=value;

}
void Game::reset(){
    score=0;
    for(int i=0;i<4;++i){
        for(int j=0;j<4;++j)
            board[i][j]=0;
    }
    spawnTile();
    spawnTile();
}

bool Game::slideRow(int row[4]){
    int temp[4]={0,0,0,0};
    int pos=0;

    for(int i=0;i<4;++i){
        if(row[i]!=0){
            temp[pos++]=row[i];
        }

    }
    for(int i=0;i<3;i++){
        if(temp[i]==temp[i+1] && temp[i]!=0){
            temp[i]*=2;
            score+=temp[i];
            temp[i+1]=0;
            ++i;
        }
    }
    pos=0;
    int result[4]={0,0,0,0};
    for(int i=0;i<4;++i){
        if(temp[i]!=0){
            result[pos++]=temp[i];
        }
    }
    bool changed=false;
    for(int i=0;i<4;++i){
        if (row[i]!= result[i]) changed=true;
        row[i]=result[i];
    }
    return changed;

}

bool Game::move(Direction dir){
    bool changed=false;
    switch(dir){
        case Direction::LEFT:
            for(int i=0;i<4;++i){
                slideRow(board[i]);
            }
            break;
        case  Direction::RIGHT:
            for(int i=0;i<4;i++){
                std::reverse(board[i],board[i]+4);
                slideRow(board[i]);
                std::reverse(board[i],board[i]+4);
            }


    }

}
Game::Game(){
    srand(time(nullptr));
    reset();

}
