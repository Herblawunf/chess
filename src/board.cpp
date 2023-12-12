//
// Created by Dylan Beharall on 10/12/2023.
//
#include "../include/board.h"
#include "../include/position.h"
#include "../include/piece.h"
#include "../include/helpers.h"
#include "../include/pieceType.h"

Board::Board() {
    board.clear();
}

void Board::assemble() {
    for (int i = 1; i < 9; i++) {
        //Piece p(pawn, white);
        board[Position(i, 2)] = Piece(pawn, white);
        board[Position(i, 7)] = Piece(pawn, black);
    }

    this->insert(Position(1, 1), Piece(rook, white));
    this->insert(Position(8, 1), Piece(rook, white));

    this->insert(Position(1, 8), Piece(rook, black));
    this->insert(Position(8, 8), Piece(rook, black));

    this->insert(Position(2, 1), Piece(knight, white));
    this->insert(Position(7, 1), Piece(knight, white));

    this->insert(Position(2, 8), Piece(knight, black));
    this->insert(Position(7, 8), Piece(knight, black));

    this->insert(Position(3, 1), Piece(bishop, white));
    this->insert(Position(6, 1), Piece(bishop, white));

    this->insert(Position(3, 8), Piece(bishop, black));
    this->insert(Position(6, 8), Piece(bishop, black));

    this->insert(Position(4, 1), Piece(queen, white));

    this->insert(Position(4, 8), Piece(queen, black));

    this->insert(Position(5, 1), Piece(king, white));

    this->insert(Position(5, 8), Piece(king, black));
}

void Board::insert(Position pos, Piece p) {
    board[pos] = p;
}

void Board::removePiece(Position pos) {
    board.erase(pos);
}

std::string Board::toString() {
    std::string ret = "  A B C D E F G H\n";

    for (int j = 8; j > 0; j--) {
        std::string add = std::to_string(j) + " ";
        for (int i = 1; i < 9; i++) {
            if (board.find(Position(i, j)) == board.end()) {
                add += ". ";
            } else {
                add += board[Position(i, j)].toChar() + " ";
            }
        }
        add += " " + std::to_string(j) + "\n";
        ret += add;
    }
    return ret + "  A B C D E F G H\n";
}

void Board::move(Move m) {
    this->removePiece(m.from);
    this->insert(m.to, m.piece);

    if (m.type == EN_PASSANT) {
        Position t = m.to;
        int tookRank;
        if (m.piece.colour == white) {
            tookRank = 5;
        } else {
            tookRank = 4;
        }
        this->removePiece(Position(t.file, tookRank));
    } else if (m.type == KINGSIDE_CASTLE) {
        if (m.piece.colour == white) {
            this->removePiece(Position(8, 1));
            this->insert(Position(6, 1), Piece(rook, white));
        } else {
            this->removePiece(Position(8, 8));
            this->insert(Position(6, 8), Piece(rook, black));
        }
    } else if (m.type == QUEENSIDE_CASTLE) {
        if (m.piece.colour == white) {
            this->removePiece(Position(1, 1));
            this->insert(Position(3, 1), Piece(rook, white));
        } else {
            this->removePiece(Position(1, 8));
            this->insert(Position(3, 8), Piece(rook, black));
        }
    }
}

bool Board::empty(Position pos) {
    return board.find(pos) == board.end();
}

bool Board::isValidMove(Move m, Move lastMove = Move(Position(), Position(), Piece(), PEACEFUL)) {
    if (empty(m.from)) return false;
    if (board[m.from] != m.piece) return false;

    int fileChange = m.to.file - m.from.file;
    int rankChange = m.to.rank - m.from.rank;
    if (rankChange == 0 && fileChange == 0) return false;

    if ((m.type == PEACEFUL || m.type == EN_PASSANT) && !empty(m.to)) return false;
    if (m.type == CAPTURE && (empty(m.to) ||
        board[m.to].colour == m.piece.colour)) return false;

    switch (m.piece.type) {
        case(pawn):
            if (m.type != PEACEFUL && m.type != CAPTURE && m.type != EN_PASSANT) return false;
            if (m.type == PEACEFUL) {
                if (fileChange != 0) return false;
                if (abs(rankChange) > 2) return false;
                if (rankChange == 2 && m.piece.colour == white) {
                    if (m.from.rank != 2) return false;
                    if (!empty(Position(m.from.file, 3))) return false;
                } else if (rankChange == -2 && m.piece.colour == black) {
                    if (m.from.rank != 7) return false;
                    if (!empty(Position(m.from.file, 6))) return false;
                } else if (abs(rankChange) == 2) return false;
            } else {
                if (abs(fileChange) != 1) return false;
                if (rankChange == 1 && m.piece.colour == white) {
                    if (m.type == EN_PASSANT) {
                        Move ideal(Position(m.to.file, 7), Position(m.to.file, 5), Piece(pawn, black), PEACEFUL);
                        if (lastMove != ideal) return false;
                    }
                } else if (rankChange == -1 && m.piece.colour == black) {
                    if (m.type == EN_PASSANT) {
                        Move ideal(Position(m.to.file, 2), Position(m.to.file, 4), Piece(pawn, white), PEACEFUL);
                        if (lastMove != ideal) return false;
                    }
                } else return false;
            }
            return true;
        case(knight):
            if (m.type != PEACEFUL && m.type != CAPTURE) return false;
            if (!((abs(fileChange) == 1 && abs(rankChange) == 2)
                || (abs(fileChange) == 2 && abs(rankChange) == 1))) return false;
            return true;
        case(bishop):
            if (abs(fileChange) != abs(rankChange)) return false;
            if (m.type != PEACEFUL && m.type != CAPTURE) return false;

            if (abs(fileChange) > 1) {
                int stepFile = m.from.file + signum(fileChange);
                int stepRank = m.from.rank + signum(rankChange);
                return isValidMove(Move(m.from, Position(stepFile, stepRank), m.piece, PEACEFUL))
                    && isValidMove(Move(Position(stepFile,stepRank), m.to, m.piece, m.type));
            } else {
                return true;
            }
        case(rook):
            if (fileChange != 0 && rankChange != 0) return false;
            if (m.type != PEACEFUL && m.type != CAPTURE) return false;

            if (abs(fileChange) > 1 || abs(rankChange) > 1) {
                if (fileChange != 0) {
                    int stepFile = m.from.file + signum(fileChange);
                    return isValidMove(Move(m.from, Position(stepFile, m.from.rank), m.piece, PEACEFUL))
                        && isValidMove(Move(Position(stepFile, m.from.rank), m.to, m.piece, m.type));
                } else {
                    int stepRank = m.from.rank + signum(rankChange);
                    return isValidMove(Move(m.from, Position(m.from.file, stepRank), m.piece, PEACEFUL))
                           && isValidMove(Move(Position(m.from.file, stepRank), m.to, m.piece, m.type));
                }
            } else {
                return true;
            }
        case(queen):
            if ((fileChange != 0 && rankChange != 0) && (abs(fileChange) != abs(rankChange))) return false;
            if (m.type != PEACEFUL && m.type != CAPTURE) return false;

            if (fileChange == 0 || rankChange == 0) {
                if (abs(fileChange) > 1 || abs(rankChange) > 1) {
                    if (fileChange != 0) {
                        int stepFile = m.from.file + signum(fileChange);
                        return isValidMove(Move(m.from, Position(stepFile, m.from.rank), m.piece, PEACEFUL))
                               && isValidMove(Move(Position(stepFile, m.from.rank), m.to, m.piece, m.type));
                    } else {
                        int stepRank = m.from.rank + signum(rankChange);
                        return isValidMove(Move(m.from, Position(m.from.file, stepRank), m.piece, PEACEFUL))
                               && isValidMove(Move(Position(m.from.file, stepRank), m.to, m.piece, m.type));
                    }
                } else {
                    return true;
                }
            } else {
                if (abs(fileChange) > 1) {
                    int stepFile = m.from.file + signum(fileChange);
                    int stepRank = m.from.rank + signum(rankChange);
                    return isValidMove(Move(m.from, Position(stepFile, stepRank), m.piece, PEACEFUL))
                           && isValidMove(Move(Position(stepFile,stepRank), m.to, m.piece, m.type));
                } else {
                    return true;
                }
            }

            return true;
        case(king):
            if (m.type == KINGSIDE_CASTLE) {
                if (m.piece.colour == white) {
                    if (m.from != Position(5, 1)) return false;
                    if (!empty(Position(6, 1)) || !empty(Position(7, 1))) return false;
                    if (empty(Position(8, 1)) || board[Position(8, 1)] != Piece(rook, white)) return false;
                } else {
                    if (m.from != Position(5, 8)) return false;
                    if (!empty(Position(6, 8)) || !empty(Position(7, 8))) return false;
                    if (empty(Position(8, 8)) || board[Position(8, 8)] != Piece(rook, black)) return false;
                }
            } else if (m.type == QUEENSIDE_CASTLE) {
                if (m.piece.colour == white) {
                    if (m.from != Position(5, 1)) return false;
                    if (!empty(Position(2, 1)) || !empty(Position(3, 1)) || !empty(Position(4, 1))) return false;
                    if (empty(Position(1, 1)) || board[Position(1, 1)] != Piece(rook, white)) return false;
                } else {
                    if (m.from != Position(5, 8)) return false;
                    if (!empty(Position(2, 8)) || !empty(Position(3, 8)) || !empty(Position(4, 8))) return false;
                    if (empty(Position(1, 8)) || board[Position(1, 8)] != Piece(rook, black)) return false;
                }
            } else {
                if (!(abs(fileChange) <= 1 && abs(rankChange) <= 1)) return false;
            }

            return true;
        default:
            break;
    }
}