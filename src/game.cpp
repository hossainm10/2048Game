#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iterator>
#include <vector>
#include <algorithm>
#include <utility>
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
                changed |= slideRow(board[i]);
            }
            break;
        case  Direction::RIGHT:
            for(int i=0;i<4;++i){
                std::reverse(board[i],board[i]+4);
                changed |= slideRow(board[i]);
                std::reverse(board[i],board[i]+4);
            }
            break;
        case Direction::UP:
            for(int i=0;i<4;++i){
                for(int j=i+1; j<4;++j){
                    std::swap(board[i][j],board[j][i]);

                }
            }
            for(int i=0;i<4;++i) changed |= slideRow(board[i]);

            for(int i=0;i<4;++i){
                for(int j=i+1;j<4;++j){
                    std::swap(board[i][j],board[j][i]);
                }
            }
            break;
        case Direction::DOWN:
            for(int i=0;i<4;++i){
                for(int j=i+1;j<4;++j){
                    std::swap(board[i][j],board[j][i]);
                }
            }
            for(int i=0;i<4;++i) std::reverse(board[i],board[i]+4);

            for(int i=0; i<4;++i) changed|=slideRow(board[i]);

            for(int i=0;i<4;++i) std::reverse(board[i],board[i]+4);

            for(int i=0;i<4;++i){
                for (int j=i+1; j<4;++j){
                    std::swap(board[i][j],board[j][i]);
                }
            }
            break;


    }
    if (changed) spawnTile();

    return changed;

}
Game::Game(){
    srand(time(nullptr));
    reset();

}

int Game::getScore() const{
    return score;
}
const int* Game::getBoard() const{
    return &board[0][0];
}

bool Game::hasWon() const{
    bool won=false;
    for(int i=0; i<4;++i){
        for(int j=0;j<4;++j){
            if(board[i][j]==2048) won = true;
        }
    }
    return won;
}

bool Game::isOver() const{
    for(int i=0;i<4;++i){
        for(int j=0;j<4;++j){
            if(board[i][j] == 0) return false;
            if(j+1<4 && board[i][j]== board[i][j+1]) return false;
            if(j+1<4 && board[i][j]==board[i+1][j]) return false;
        }
    }
    return true;
}
