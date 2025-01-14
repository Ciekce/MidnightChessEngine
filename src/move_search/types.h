#pragma once
#include "search_constants.h"
#include "../move_gen/types/move.h"
#include "tables/pv_table.h"
#include <vector>

struct ScoredMove {
	Move move;
	i32 score{};
};

using ScoredMoves = std::vector<ScoredMove>;

struct BestMoveSearchParameters {
	i16 depth = MAX_DEPTH;
	i32 hard_time_limit = DEFAULT_SEARCH_TIME;
	i32 soft_time_limit = DEFAULT_SEARCH_TIME;
	bool debug_info = false;
};

typedef Move Line[MAX_DEPTH];
extern std::ostream& operator<<(std::ostream& os, const Line& line);

struct PVSData {
	Move best_move;
	Move final_best_move;
	bool search_completed{};
	i32 value{};
	// triangular-table-table
	PV pv{};
	u64 nodes_searched{};
	i32 seldepth{};

	array<Move, MAX_PLY> moves_made{};
	i32 time_limit{};

	array<Move, MAX_PLY> excluded_moves{};
	array<array<u64, NSQUARES>, NSQUARES> nodes_spend{};
	array<i32, MAX_PLY> evals{};
};
