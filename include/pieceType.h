//
// Created by Dylan Beharall on 10/12/2023.
//

#ifndef CHESS_PIECETYPE_H
#define CHESS_PIECETYPE_H

enum PieceType
{
    pawn,
    knight,
    bishop,
    rook,
    queen,
    king,
};

enum Colour
{
    black,
    white,
};

Colour opposite(Colour c);

#endif //CHESS_PIECETYPE_H
