#include <cstdint>
#include <cassert>
#include <iostream>
#include <iomanip>

#include "bitboard.hpp"
#include "types.hpp"

int leadingBit(uint64_t bitboard) {
    // Counts from the first bit
    assert(bitboard);
    return __builtin_ctzll(bitboard);
}

int trailingBit(uint64_t bitboard) {
    // Counts from the last bit
    assert(bitboard);
    return __builtin_clzll(bitboard);
}

int popLeadingBit(uint64_t& bitboard) {
    int pos = leadingBit(bitboard);
    bitboard ^= 1ull << pos;
    return pos;
}

int popTrailingBit(uint64_t& bitboard) {
    int pos = trailingBit(bitboard);
    bitboard ^= 0x8000000000000000ull >> pos;
    return pos;
}

int popCount(uint64_t bitboard) {
    return __builtin_popcountll(bitboard);
}

uint64_t flipVertical(uint64_t bitboard) {
    uint64_t k1 = 0x00FF00FF00FF00FFull;
    uint64_t k2 = 0x0000FFFF0000FFFFull;
    bitboard = ((bitboard >>  8) & k1) | ((bitboard & k1) <<  8);
    bitboard = ((bitboard >> 16) & k2) | ((bitboard & k2) << 16);
    bitboard = ( bitboard >> 32)       | ( bitboard       << 32);
    return bitboard;
}

int getFile(int square) {
    return square % 8;
}
int getRank(int square) {
    return square / 8;
}

uint64_t getFileMask(int square) {
    return FILES_MASK[getFile(square)];
}

uint64_t getRankMask(int square) {
    return RANKS_MASK[getRank(square)];
}

uint64_t getDiagMask(int square) {
    return DIAGS_MASK[getRank(square) + getFile(square)];
}

uint64_t getAntiDiagMask(int square) {
    return flipVertical(DIAGS_MASK[7 - getRank(square) + getFile(square)]);
}

uint64_t knightSquares(uint64_t knights) {
    uint64_t left1 = (knights >> 1) & NOT_FILE_H;
    uint64_t left2 = (knights >> 2) & NOT_FILE_HG;
    uint64_t right1 = (knights << 1) & NOT_FILE_A;
    uint64_t right2 = (knights << 2) & NOT_FILE_AB;

    uint64_t height1 = left1 | right1;
    uint64_t height2 = left2 | right2;
    
    uint64_t knightSquares = (height1 << 16) | (height1 >> 16) | (height2 << 8) | (height2 >> 8);
    return knightSquares;
}

bool pawnAttackers(int square, uint64_t enemyPawns, bool isWhiteTurn) {
    uint64_t currPiece = 1ull << square;

    // prevent currPiece from teleporting to other side of the board with bit shifts
    uint64_t left  = currPiece & NOT_FILE_A;
    uint64_t right = currPiece & NOT_FILE_H;
    
    uint64_t upPawns   = (left >> 9) | (right >> 7); 
    uint64_t downPawns = (left << 7) | (right << 9); 
    return isWhiteTurn ? upPawns & enemyPawns : downPawns & enemyPawns;
}

bool kingAttackers(int square, uint64_t enemyKings) {
    uint64_t currPiece = 1ull << square;

    // prevent currPiece from teleporting to other side of the board with bit shifts
    uint64_t left = currPiece & NOT_FILE_A;
    uint64_t right = currPiece & NOT_FILE_H;
    
    currPiece |= (left >> 1);
    currPiece |= (right << 1);
    
    // up one row and down one row respectively
    currPiece |= (currPiece >> 8) | (currPiece << 8);
    return currPiece & enemyKings;
}

// below functions are for debugging and testing

void printHex(uint64_t bitboard) {
    std::cout << "0x" << std::setw(16) << std::setfill('0') << std::hex <<  bitboard << "ull\n" << std::dec;
}

void printBitboard(uint64_t bitboard) {
    std::cout << "------------\n";
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            bool bit = 1ull << (8 * i + j) & bitboard;
            std::cout << bit << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "------------\n";
}

uint64_t arrayToBitboardNotEmpty(std::array<pieceTypes, BOARD_SIZE> board) {
    uint64_t result = 0ull;
    for (size_t i = 0; i < board.size(); i++) {
        if (board.at(i) != EmptyPiece) {
            result |= (1ull << i);
        }
    }
    return result;
}

uint64_t arrayToBitboardPieceType(std::array<pieceTypes, BOARD_SIZE> board, pieceTypes piece) {
    uint64_t result = 0ull;
    for (size_t i = 0; i < board.size(); i++) {
        if (board.at(i) == piece) {
            result |= (1ull << i);
        }
    }
    return result;
}