#pragma once
template<Color color>
constexpr Score evaluate_rooks(Position& board) {
	Score score = Score();
	Bitboard rooks = board.bitboard_of(color, ROOK);
	Bitboard us_pieces = board.all_pieces<color>();
	Bitboard them_pieces = board.all_pieces<~color>();
	const Bitboard board_open_files = open_files(board);
	const Bitboard board_semi_open_files = semi_open_files<color>(board);
	while (rooks) {
		Square rook_square = pop_lsb(&rooks);
		const Bitboard rook_square_bb = SQUARE_BB[rook_square];
		score += PIECE_VALUES[ROOK];
		score += read_psqt<color>(ROOK, rook_square);
		Bitboard pseudo_legal_moves = attacks<ROOK>(rook_square, them_pieces | us_pieces) & ~us_pieces;
		score += ROOK_MOBILITY * pop_count(pseudo_legal_moves);
		const bool on_open_file = rook_square_bb & board_open_files;
		const bool on_semi_open_file = rook_square_bb & board_semi_open_files;
		score += (OPEN_FILE_BONUS[ROOK] * on_open_file) + (SEMI_OPEN_FILE_BONUS[ROOK] * on_semi_open_file);
	}
	return score;
}