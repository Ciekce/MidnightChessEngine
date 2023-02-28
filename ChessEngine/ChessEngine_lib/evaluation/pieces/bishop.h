#ifndef BISHOP_H
#define BISHOP_H

template<Color color>
constexpr Score evaluate_bishops(Position& board) {
	Score score = Score();
	Bitboard bishops = board.bitboard_of(color, BISHOP);
	while (bishops) {
		Square bishop_square = pop_lsb(&bishops);
		score += PIECE_VALUES[BISHOP];
		score += read_pstq<color>(BISHOP, bishop_square);
	}
	return score;
}

#endif // BISHOP_H