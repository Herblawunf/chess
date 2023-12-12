//
// Created by Dylan Beharall on 10/12/2023.
//
#include <unordered_map>
#include <string>
#include "position.h"
#include "piece.h"
#include "move.h"

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

class Board {
public:
    std::unordered_map<Position, Piece> board;

    Board();

    void assemble();

    void insert(Position pos, Piece p);

    void removePiece(Position pos);

    void move(Move m);

    bool empty(Position pos);

    bool isValidMove(Move m, Move lastMove);

    std::string toString();
};

#endif //CHESS_BOARD_H
