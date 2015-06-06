#pragma once
#include "base.h"
#include "stone.h"
#include "board.h"

namespace oth
{
	class board_increment
	{
	private:
		board boa;
		unsigned char x;
		unsigned char y;

	public:
		board_increment() :
			boa(),
			x(0),
			y(0)
		{}

	public:

		bool increment_plus()
		{
			const stone stn = boa.get_d(this->x, this->y);
			if (stn == NONE) {
				boa.set_d(this->x, this->y, BLACK);
			}
			else if (stn == BLACK) {
				boa.set_d(this->x, this->y, WHITE);
			}
			else {
				if (this->y == 7) {
					return false;
				}
				else {
					boa.set_d(x, y, NONE);
					if (x == 7) {
						this->x = 0;
						this->y = 1;
					}
					else if (y > 0) {
						this->y = this->y + 1;
					}
					else {
						this->x = this->x + 1;
					}
				}
				this->increment_plus();
			}
			return true;
		}
	};
}