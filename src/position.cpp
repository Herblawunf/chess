//
// Created by Dylan Beharall on 10/12/2023.
//

#include "../include/position.h"

Position::Position(int f, int r) {
    file = f;
    rank = r;
}

std::string Position::toString() const {
    return "abcdefgh"[file - 1] + std::to_string(rank);
}

bool Position::valid() const {
    return 0 < file && file < 9 && 0 < rank && rank < 9;
}

bool Position::operator==(const Position &Ref) const {
    return file == Ref.file && rank == Ref.rank;
}

bool Position::operator!=(const Position &Ref) const {
    return file != Ref.file || rank != Ref.rank;
}

bool Position::operator<(const Position &ref) const {
    if (rank < ref.rank) return true;
    if (rank > ref.rank) return false;
    return file < ref.file;
}