#include <iostream>
#include "logic.h"
#include "board_increment.h"
using namespace oth;

void main()
{
	board_increment incr;
	bool is_end = false;
	
	do {
		board boa = incr.get_board();
		boa.print();
		
	} while (incr.increment_plus());

}
