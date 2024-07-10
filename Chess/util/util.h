#ifndef UTIL_H
#define UTIL_H

#include <math.h> // IWYU pragma: keep
#include <stdlib.h> // IWYU pragma: keep
#include <string.h> // IWYU pragma: keep
#include "stdio.h" // IWYU pragma: keep
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

#define BOARD_LIMIT 64
#define POSITIONS_PER_SQUARE 8

#define PIECE_LIMITS 16
#define BOARD_SIZE 576
#define POSITIONS_PER_PIECE 8
#define WHITE_PAWN_INDEX 5
#define BLACK_PAWN_INDEX 11

typedef enum
{
    A1,    B1,    C1,    D1,    E1,    F1,    G1,    H1,
    A2,    B2,    C2,    D2,    E2,    F2,    G2,    H2,
    A3,    B3,    C3,    D3,    E3,    F3,    G3,    H3,
    A4,    B4,    C4,    D4,    E4,    F4,    G4,    H4,
    A5,    B5,    C5,    D5,    E5,    F5,    G5,    H5,
    A6,    B6,    C6,    D6,    E6,    F6,    G6,    H6,
    A7,    B7,    C7,    D7,    E7,    F7,    G7,    H7,
    A8,    B8,    C8,    D8,    E8,    F8,    G8,    H8,
    InvalidPosition
} BoardPosition;

typedef enum {
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
} PieceType;

typedef enum {
    WHITE = 0,
    DARK = 1
} ChessColors;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-braces"


#pragma GCC diagnostic pop

#endif