//
// Created by Dylan Beharall on 11/12/2023.
//

#include "../include/pieceType.h"

Colour opposite(Colour c) {
    if (c == white) return black;
    return white;
}
