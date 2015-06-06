#pragma once
#include "base.h"
#include "board.h"


namespace oth
{
	class logic
	{
	public:
		template<class _Ver, class _Hol>
		static unsigned char get_reverse_count(const board& target, const unsigned char x, const unsigned char y, const stone stn)
		{
			if (target.get_d(x, y) != NONE) {
				return 0;
			}
			const stone reverse_stone = stone_utility::get_reverse(stn);
			char curr_y = y + _Ver::value;
			char curr_x = x + _Hol::value;
			unsigned char counter = 0;
			
			while (true) {
				if (board::is_valid_position_d(curr_x, curr_y)) {
					const stone curr_stone = target.get_d(curr_x, curr_y);
					if (curr_stone == reverse_stone) {
						counter += 1;
						curr_x += _Hol::value;
						curr_y += _Ver::value;
					}
					else {
						if (curr_stone == NONE) {
							counter = 0;
						}
						break;
					}
				}
				else {
					counter = 0;
					break;
				}
			}
			return counter;
		}

		template<class _Ver, class _Hol>
		static void set(board& target, const unsigned char x, const unsigned char y, const stone stn, unsigned char reverse_count)
		{
			if (!reverse_count) {
				return;
			}
			char curr_y = y;
			char curr_x = x;

			do {
				curr_y += _Ver::value;
				curr_x += _Hol::value;
				target.set_d(curr_x, curr_y, stn);
				reverse_count -= 1;
			} while (reverse_count);
		}

		static board set(const board& target, const unsigned char x, const unsigned char y, const stone stn)
		{
			board result_board = target;
			logic::set<vector::up, vector::nothing>(result_board, x, y, stn, logic::get_reverse_count<vector::up, vector::nothing>(target, x, y, stn));
			logic::set<vector::up, vector::right>(result_board, x, y, stn, logic::get_reverse_count<vector::up, vector::right>(target, x, y, stn));
			logic::set<vector::nothing, vector::right>(result_board, x, y, stn, logic::get_reverse_count<vector::nothing, vector::right>(target, x, y, stn));
			logic::set<vector::down, vector::right>(result_board, x, y, stn, logic::get_reverse_count<vector::down, vector::right>(target, x, y, stn));
			logic::set<vector::down, vector::nothing>(result_board, x, y, stn, logic::get_reverse_count<vector::down, vector::nothing>(target, x, y, stn));
			logic::set<vector::down, vector::left>(result_board, x, y, stn, logic::get_reverse_count<vector::down, vector::left>(target, x, y, stn));
			logic::set<vector::nothing, vector::left>(result_board, x, y, stn, logic::get_reverse_count<vector::nothing, vector::left>(target, x, y, stn));
			logic::set<vector::up, vector::left>(result_board, x, y, stn, logic::get_reverse_count<vector::up, vector::left>(target, x, y, stn));
			if (target != result_board) {
				result_board.set_d(x, y, stn);
			}
			return result_board;
		}
	};

}