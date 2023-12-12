//
// Created by Dylan Beharall on 10/12/2023.
//

#include "../include/piece.h"

std::string Piece::toChar() const {
    switch (type) {
        case pawn:
            if (colour == white) {
                return "\u2659";
            } else {
                return "\u265F";
            }
            break;
        case knight:
            if (colour == white) {
                return "\u2658";
            } else {
                return "\u265E";
            }
            break;
        case bishop:
            if (colour == white) {
                return "\u2657";
            } else {
                return "\u265D";
            }
            break;
        case rook:
            if (colour == white) {
                return "\u2656";
            } else {
                return "\u265C";
            }
            break;
        case queen:
            if (colour == white) {
                return "\u2655";
            } else {
                return "\u265B";
            }
            break;
        case king:
            if (colour == white) {
                return "\u2654";
            } else {
                return "\u265A";
            }
            break;
    }
}

Piece::Piece(PieceType p, Colour c) {
    type = p;
    colour = c;
}

bool Piece::operator<(const Piece &ref) const {
    return ref.toChar() < this->toChar();
}

bool Piece::operator==(const Piece &ref) const {
    return ref.toChar() == this->toChar();
}

bool Piece::operator!=(const Piece &ref) const {
    return ref.toChar() != this->toChar();
}