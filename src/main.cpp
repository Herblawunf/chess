//
// Created by Dylan Beharall on 10/12/2023.
//
#include <iostream>
#include "../include/piece.h"
#include "../include/position.h"
#include "../include/board.h"

using namespace std;

int main() {
    Board b;

    b.assemble();

    Move m(Position(7, 1), Position(6, 3), Piece(knight, white), PEACEFUL);
    Move m1(Position (5, 2), Position(5, 3), Piece(pawn, white), PEACEFUL);
    Move m2(Position(6, 1), Position(5, 2), Piece(bishop, white), PEACEFUL);
    Move m3(Position(5, 1), Position(7, 1), Piece(king, white), KINGSIDE_CASTLE);

    if (b.isValidMove(m, Move())){
        b.move(m);
    }
    if (b.isValidMove(m1, Move())){
        b.move(m1);
    }
    if (b.isValidMove(m2, Move())){
        b.move(m2);
    }
    if (b.isValidMove(m3, Move())){
        b.move(m3);
    }

    cout << b.toString() << endl;

    return 0;
}