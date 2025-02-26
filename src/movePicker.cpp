#include <vector>

#include "movePicker.hpp"
#include "board.hpp"
#include "move.hpp"
#include "types.hpp"

MovePicker::MovePicker(std::vector<BoardMove>&& a_moves) {
    this->moves = a_moves;
    this->moveScores = std::vector<int>(moves.size());
    this->size = moves.size();
    this->movesPicked = 0;
};

// Searching moves that are likely to be better helps with pruning in search. This is move ordering.
// More promising moves are given higher scores and then searched first.
void MovePicker::assignMoveScores(const Board& board) {
    size_t i = 0;
    for (BoardMove move: this->moves) {
        // capture
        // moveGen outputs least valuable piece moves first, so least value captures is automatic 
        if (board.getPiece(move.pos2) != EmptyPiece) {
            this->moveScores[i] = 1;
        }
        // default
        else {
            this->moveScores[i] = 0;
        }
        i++;
    }
}

bool MovePicker::movesLeft() const {
    return this->movesPicked < this->size;
}

// Due to pruning, we don't need to sort the entire array of moves for move ordering.
// When sorting only small portions of arrays, using insertion sort is faster.
BoardMove MovePicker::pickMove() {
    auto begin = this->moveScores.begin() + this->movesPicked;
    auto end = this->moveScores.end();
    size_t maxIndex = std::distance(this->moveScores.begin(), std::max_element(begin, end));
    
    std::swap(this->moveScores[maxIndex], this->moveScores[movesPicked]);
    std::swap(this->moves[maxIndex], this->moves[movesPicked]);
    BoardMove move = this->moves[movesPicked];
    
    this->movesPicked++;
    return move;
}