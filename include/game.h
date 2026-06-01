#pragma once

enum class Direction{ UP,DOWN, LEFT,RIGHT};

class Game{
    public:
        Game();
        void reset();
        bool move(Direction dir);
        bool isOver() const;
        bool hasWon() const;
        int getScore() const;
        const int* getBoard() const;
    private:
        int board[4][4];
        int score;
        void spawnTile();
        bool canMove() const;
        bool slideRow(int row[4]);
};
