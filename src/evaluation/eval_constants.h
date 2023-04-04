#pragma once
#include "move_generation/types.h"
#include "types.h"

//
// Created by Archishmaan Peyyety on 1/10/23.
//

// If this is updated be sure compute_game_phase loop is also updated. Currently only checks non-zeros.
constexpr int GAME_PHASE_BONUS[NPIECE_TYPES] = {
		0, 1, 1, 2, 4, 0
};

constexpr Score PIECE_VALUES[] = {S(103, 105), S(429, 361), S(425, 353), S(571, 693), S(1353, 1267), S(0, 0)};
constexpr Score PAWN_TABLE[] = {S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(203, 169), S(187, 158), S(130, 153), S(208, 96), S(146, 112), S(171, 109), S(-16, 174), S(21, 192), S(-11, 109), S(11, 101), S(49, 72), S(62, 47), S(74, 35), S(89, 39), S(5, 76), S(-0, 87), S(-10, 33), S(1, 19), S(7, 12), S(33, -15), S(28, -4), S(39, 3), S(9, 15), S(-7, 20), S(-17, 15), S(-14, 9), S(1, -6), S(20, -15), S(19, -6), S(20, -10), S(2, -1), S(-13, 0), S(-17, 2), S(-27, 6), S(-7, -3), S(1, -5), S(3, 9), S(-10, 8), S(-12, -2), S(-26, -2), S(-22, 21), S(-18, 12), S(-19, 22), S(-18, 16), S(-15, 28), S(-0, 21), S(-1, 3), S(-41, 4), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0), S(0, 0)};
constexpr Score KNIGHT_TABLE[] = {S(-223, -23), S(-138, 13), S(-59, 39), S(-9, 15), S(96, 9), S(-144, 33), S(-45, -22), S(-140, -82), S(-29, 6), S(-35, 30), S(70, 23), S(32, 58), S(27, 49), S(87, 13), S(-20, 25), S(-12, -2), S(-24, 9), S(59, 26), S(73, 58), S(98, 61), S(119, 38), S(138, 40), S(77, 25), S(48, -13), S(28, 17), S(46, 44), S(59, 67), S(86, 71), S(54, 78), S(89, 69), S(43, 49), S(48, 20), S(8, 20), S(22, 34), S(50, 61), S(51, 70), S(65, 64), S(51, 63), S(70, 37), S(17, 28), S(-8, -14), S(15, 27), S(38, 25), S(43, 55), S(57, 40), S(47, 20), S(40, 3), S(-1, 14), S(-25, -20), S(-14, 8), S(15, 16), S(26, 37), S(26, 44), S(32, 9), S(8, 19), S(24, -25), S(-113, -5), S(-6, -20), S(-31, 14), S(-14, 26), S(7, 11), S(7, 14), S(-3, -7), S(-41, -33)};
constexpr Score BISHOP_TABLE[] = {S(-34, 27), S(15, 25), S(-97, 45), S(-54, 42), S(-48, 49), S(-77, 40), S(7, 27), S(6, 20), S(-32, 41), S(20, 24), S(3, 40), S(-29, 37), S(26, 35), S(52, 25), S(11, 29), S(-26, 35), S(18, 28), S(40, 25), S(62, 18), S(32, 26), S(58, 17), S(71, 29), S(77, 28), S(27, 42), S(-4, 31), S(29, 32), S(17, 37), S(73, 23), S(51, 24), S(55, 22), S(33, 43), S(16, 41), S(9, 22), S(18, 30), S(24, 34), S(51, 30), S(58, 18), S(20, 28), S(18, 20), S(42, 11), S(17, 14), S(38, 25), S(30, 25), S(27, 24), S(28, 34), S(40, 19), S(34, 16), S(36, 10), S(26, 8), S(39, 4), S(37, 13), S(16, 27), S(27, 21), S(25, 8), S(56, 23), S(16, 3), S(35, -3), S(28, 17), S(7, 37), S(12, 25), S(-7, 33), S(5, 38), S(-7, 33), S(7, 4)};
constexpr Score ROOK_TABLE[] = {S(25, 54), S(31, 50), S(-7, 61), S(9, 55), S(43, 50), S(12, 54), S(34, 48), S(64, 47), S(10, 56), S(9, 59), S(33, 52), S(43, 55), S(65, 37), S(95, 28), S(27, 50), S(54, 41), S(-15, 51), S(15, 45), S(27, 44), S(28, 43), S(53, 29), S(89, 26), S(133, 9), S(39, 26), S(-14, 43), S(-12, 44), S(11, 47), S(32, 37), S(8, 45), S(38, 39), S(10, 33), S(1, 38), S(-28, 39), S(-32, 47), S(-20, 46), S(-13, 43), S(-6, 40), S(10, 24), S(30, 25), S(-6, 22), S(-32, 24), S(-23, 34), S(-19, 26), S(-12, 28), S(-11, 28), S(6, 19), S(21, 16), S(-1, 8), S(-35, 22), S(-14, 20), S(-18, 31), S(-12, 27), S(1, 23), S(14, 14), S(15, 9), S(-58, 29), S(0, 33), S(-0, 32), S(7, 31), S(17, 22), S(15, 23), S(20, 25), S(-6, 28), S(7, 13)};
constexpr Score QUEEN_TABLE[] = {S(-28, -2), S(-37, 50), S(-27, 48), S(7, 14), S(65, 24), S(68, 11), S(75, 8), S(70, 8), S(-14, 15), S(-47, 38), S(-19, 56), S(-12, 63), S(-31, 84), S(32, 62), S(13, 60), S(64, 15), S(-2, -0), S(-3, 11), S(6, 14), S(-32, 86), S(-10, 85), S(87, 41), S(95, 18), S(12, 78), S(-12, 1), S(-10, 31), S(-15, 43), S(-15, 57), S(-7, 79), S(24, 55), S(27, 80), S(14, 79), S(1, -17), S(-3, 34), S(12, 10), S(-2, 54), S(12, 32), S(20, 49), S(28, 45), S(19, 20), S(-15, 3), S(26, -48), S(21, -2), S(16, -17), S(21, -1), S(24, 5), S(37, -6), S(14, 25), S(-19, -4), S(16, -51), S(32, -52), S(22, -17), S(34, -38), S(36, -55), S(36, -70), S(3, -32), S(13, -31), S(2, -37), S(24, -40), S(30, 17), S(22, -40), S(10, -59), S(21, -62), S(-18, -65)};
constexpr Score KING_TABLE[] = {S(-104, -98), S(202, -84), S(195, -61), S(142, -59), S(-138, 2), S(-77, 24), S(101, -17), S(1, -32), S(205, -67), S(92, 10), S(103, 9), S(121, -0), S(63, 13), S(104, 21), S(3, 36), S(-167, 25), S(42, 3), S(118, 13), S(125, 22), S(55, 15), S(93, 8), S(145, 36), S(177, 30), S(-25, 11), S(9, -15), S(49, 19), S(30, 33), S(8, 40), S(-20, 36), S(23, 30), S(14, 25), S(-113, 11), S(-85, -17), S(79, -18), S(8, 22), S(-48, 44), S(-46, 40), S(-31, 25), S(-29, 10), S(-94, -10), S(-31, -25), S(-9, -1), S(-25, 15), S(-39, 30), S(-28, 29), S(-25, 15), S(-13, 1), S(-43, -18), S(-23, -32), S(-32, -10), S(-14, 8), S(-78, 24), S(-47, 19), S(-40, 13), S(-35, 0), S(-29, -26), S(-51, -78), S(-17, -46), S(-57, -12), S(-75, -5), S(-83, -12), S(-49, -14), S(-32, -26), S(-29, -77)};
constexpr Score OPEN_FILE_BONUS[] = {S(0, 0), S(0, 0), S(0, 0), S(48, 2), S(-3, 29), S(-60, -0)};
constexpr Score SEMI_OPEN_FILE_BONUS[] = {S(0, 0), S(0, 0), S(0, 0), S(19, 9), S(2, 25), S(-24, 12)};
constexpr Score PAWN_PROTECTION[] = {S(4, 3), S(1, 20), S(-3, 21), S(0, 0), S(0, 0), S(0, 0)};
constexpr Score ATTACKED_BY_PAWN[] = {S(0, 0), S(-44, -14), S(-56, -39), S(-90, 22), S(-59, 11), S(0, 0)};
constexpr Score KING_RING_ATTACK_BONUS[] = {S(18, -12), S(32, -12), S(20, -5), S(35, -9), S(31, 7), S(0, 0)};
constexpr Score CHECK_BONUS[] = {S(237, -22), S(106, -1), S(65, 48), S(123, -15), S(69, 73), S(0, 0)};
constexpr Score KING_PAWN_SHIELD[] = {S(39, -14), S(31, -8)};
constexpr Score PASSED_PAWN_BONUS = S(-0, 23);
constexpr Score BLOCKED_PASSED_PAWN_PENALTY = S(5, -20);
constexpr Score ISOLATED_PAWN_PENALTY = S(-16, -14);
constexpr Score DOUBLED_PAWN_PENALTY = S(-16, -18);
constexpr Score BISHOP_PAIR_BONUS = S(29, 73);
constexpr Score KNIGHT_MOBILITY[9] = {S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1)};
constexpr Score BISHOP_MOBILITY[14] = {S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1)};
constexpr Score ROOK_MOBILITY[15] = {S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 0)};
constexpr Score QUEEN_MOBILITY[32] = {S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 0), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 1), S(0, 0), S(0, 0), S(0, 0)};

template<Color color, PieceType piece_type>
constexpr Score read_psqt(Square square) {
	if (color == WHITE) square = ~square;
	switch (piece_type) {
		case PAWN: return PAWN_TABLE[square];
		case KNIGHT: return KNIGHT_TABLE[square];
		case BISHOP: return BISHOP_TABLE[square];
		case ROOK: return ROOK_TABLE[square];
		case QUEEN: return QUEEN_TABLE[square];
		case KING: return KING_TABLE[square];
		default: return {};
	}
}
