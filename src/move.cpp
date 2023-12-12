//
// Created by Dylan Beharall on 11/12/2023.
//
#include "../include/move.h"

Move::Move(Position f, Position t, Piece p, MoveType ty) {
    from = f;
    to = t;
    piece = p;
    type = ty;
}

bool Move::operator!=(const Move &ref) const {
    return ref.from != from || ref.to != to || ref.piece != piece || ref.type != type;
}