#pragma once
#include "move_generation/types.h"

int lmr_reduction(const bool& pv_node, const int& move_idx, const int& depth, const Move& legal_move);
int nmp_reduction(const int& depth, const int& beta, const int& static_eval);