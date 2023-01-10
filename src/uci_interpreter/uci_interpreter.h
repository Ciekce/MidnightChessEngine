//
// Created by Archishmaan Peyyety on 1/9/23.
//
#include <algorithm>
#include <iostream>
#include "tables.h"
#include "position.h"
#include "types.h"
#include "search.h"


using namespace std;
Move uciToMove(const std::string& moveStr, Position& position) {
	Move move = Move(moveStr.substr(0, 4));
	// Pawn Promotion
	if (moveStr.size() == 5) {
		/*
		Could be dangerous if order in enum is changed!
		int promotionType = position.at(move.to()) == NO_PIECE ? PR_KNIGHT : PC_KNIGHT;
		if (moveStr.at(4) == 'n') return Move(move.from(), move.to(), (MoveFlag) promotionType);
		if (moveStr.at(4) == 'b') return Move(move.from(), move.to(), (MoveFlag) (promotionType + 1));
		if (moveStr.at(4) == 'r') return Move(move.from(), move.to(), (MoveFlag) (promotionType + 2));
		if (moveStr.at(4) == 'q') return Move(move.from(), move.to(), (MoveFlag) (promotionType + 3));
		*/
		// Quiet Promotion
		if (position.at(move.to()) == NO_PIECE) {
			if (moveStr.at(4) == 'q') return Move(move.from(), move.to(), PR_QUEEN);
			if (moveStr.at(4) == 'b') return Move(move.from(), move.to(), PR_BISHOP);
			if (moveStr.at(4) == 'n') return Move(move.from(), move.to(), PR_KNIGHT);
			if (moveStr.at(4) == 'r') return Move(move.from(), move.to(), PR_ROOK);
		}
		if (moveStr.at(4) == 'q') return Move(move.from(), move.to(), PC_QUEEN);
		if (moveStr.at(4) == 'b') return Move(move.from(), move.to(), PC_BISHOP);
		if (moveStr.at(4) == 'n') return Move(move.from(), move.to(), PC_KNIGHT);
		if (moveStr.at(4) == 'r') return Move(move.from(), move.to(), PC_ROOK);
	}

	// En Passant
	if (position.at(move.to()) == NO_PIECE && type_of(position.at(move.from())) == PAWN &&
		file_of(move.to()) != file_of(move.from())) {
		return Move(move.from(), move.to(), EN_PASSANT);
	}

	if (type_of(position.at(move.from())) == PAWN && rank_of(move.to()) - rank_of(move.from()) == 2) {
		return Move(move.from(), move.to(), DOUBLE_PUSH);
	}

	// Castle
	if (type_of(position.at(move.from())) == KING) {
		if (moveStr == "e1g1" || moveStr == "e8g8") return Move(move.from(), move.to(), OO);
		if (moveStr == "e1c1" || moveStr == "e8c8") return Move(move.from(), move.to(), OOO);
	}

	// Capture
	if (position.at(move.to()) != NO_PIECE) {
		return Move(move.from(), move.to(), CAPTURE);
	}

	return {move.from(), move.to(), QUIET};
}
vector<string> split(const string& s, const string& delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	string token;
	vector<string> res;

	while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
		token = s.substr (pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back (token);
	}

	res.push_back (s.substr (pos_start));
	return res;
}

void read_uci(const string& diagnostics_file_path) {
	initialise_all_databases();
	zobrist::initialise_zobrist_keys();
	Position p;
	const std::string& default_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	Position::set(default_fen, p);

	string input_line; //to read the command given by the GUI

	cout.setf(ios::unitbuf);// Make sure that the outputs are sent straight away to the GUI

	ofstream diagnostics_file;
	diagnostics_file.open(diagnostics_file_path);
	while (getline(cin, input_line)) {
		diagnostics_file << input_line << std::endl;
		if (input_line == "uci") {
			cout << "id name MidnightChessEngine" << endl;
			cout << "id author Archishmaan Peyyety" << endl;
			cout << "uciok" << endl;
		} else if (input_line == "quit") {
			cout << "Bye Bye" << endl;
			break;
		} else if (input_line == "isready") {
			cout << "readyok" << endl;
		} else if (input_line == "ucinewgame") {
			; // nothing to do
		}
		if (input_line.substr(0, 23) == "position startpos moves") {
			Position::set(default_fen, p);
			vector<string> uciMoves = split(input_line.substr(24, input_line.size() - 24), " ");
			for (const std::string& uciMove : uciMoves) {
				Move nextMove = uciToMove(uciMove, p);
				if (p.turn() == BLACK) p.play<BLACK>(nextMove);
				else p.play<WHITE>(nextMove);
			}
		} else if (input_line == "stop") {
			; // nothing to do
		} else if (input_line.substr(0, 2 ) == "go") {
			// Received a command like: "go wtime 300000 btime 300000 winc 0 binc 0"
			BestMoveSearchResults results;
			if (p.turn() == BLACK) results = best_move<BLACK>(p);
			else results = best_move<WHITE>(p);
			diagnostics_file << "Predicted Best Move: " << results.best_move << ":" << results.depth_searched << std::endl;
			diagnostics_file << "Time Searched: " << results.time_searched << std::endl;
			cout << "bestmove " << results.best_move << endl;
			//Output like: "bestmove h7h5"
		}
	}
	diagnostics_file.close();
}