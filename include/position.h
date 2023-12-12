//
// Created by Dylan Beharall on 10/12/2023.
//
#include <string>

#ifndef CHESS_POSITION_H
#define CHESS_POSITION_H

class Position {
public:
    int file;
    int rank;

    Position(): file(1), rank(1) {};

    Position(int f, int r);

    std::string toString() const;

    bool valid() const;

    bool operator == (const Position &ref) const;

    bool operator != (const Position &ref) const;

    bool operator <(const Position &ref) const;
};

namespace std {
    template <>
    struct hash<Position> {
        std::size_t operator()(const Position& p) const {
            // Use a combination of the hash values of x and y for the Position
            return hash<int>()(p.file) ^ hash<int>()(p.rank);
        }
    };
}

#endif //CHESS_POSITION_H
