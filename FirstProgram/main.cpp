#include <iostream>
#include "logic.h"
#include "board_increment.h"
using namespace oth;

void main()
{
	std::vector<point> p = board_increment::get_point_list<line::vertical, line::horizontal, line::right_cross>((unsigned char)1, (unsigned char)1);
	std::cout << p.size() << std::endl;

}
