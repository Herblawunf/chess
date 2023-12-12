//
// Created by Dylan Beharall on 10/12/2023.
//
#include "position.h"
#include "piece.h"

#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

enum MoveType {
    PEACEFUL,
    CAPTURE,
    EN_PASSANT,
    KINGSIDE_CASTLE,
    QUEENSIDE_CASTLE,
};

class Move {
public:
    Position from;
    Position to;
    Piece piece;
    MoveType type;

    Move(): from(Position(1, 1)), to(Position(1,1)), piece(Piece(rook, white)), type(PEACEFUL) {};

    Move(Position f, Position t, Piece p, MoveType ty);

    bool operator != (const Move &ref) const;
};

#endif //CHESS_MOVE_H
