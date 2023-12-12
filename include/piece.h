//
// Created by Dylan Beharall on 10/12/2023.
//
#include "pieceType.h"
#include <string>

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

class Piece {
public:
    PieceType type;
    Colour colour;

    Piece(): type(pawn), colour(white) {}

    Piece(PieceType p, Colour c);

    std::string toChar() const;

    bool operator == (const Piece &ref) const;

    bool operator <(const Piece &ref) const;

    bool operator!=(const Piece &ref) const;
};

namespace std {
    template <>
    struct hash<Piece> {
        std::size_t operator()(const Piece& p) const {
            // Use a combination of the hash values of x and y for the Position
            return hash<PieceType>()(p.type) ^ hash<Colour>()(p.colour);
        }
    };
}

#endif //CHESS_PIECE_H
