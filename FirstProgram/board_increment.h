#pragma once
#include "base.h"
#include "stone.h"
#include "board.h"
#include "point.h"
#include <vector>

namespace oth
{
	class board_increment
	{
	private:
		board boa;

	public:
		board_increment() :
			boa()
		{}

	public:
	
		board get_board() const
		{
			return this->boa;
		}


		template<class _Fir, class _Sec, class _Thi, class _Fou>
		static std::vector<point> get_point_list(const unsigned char x, const unsigned char y)
		{
			std::vector<point> result;
			board_increment::get_point_list_impl<_Fir::value | _Sec::value | _Thi::value | _Fou::value | 0x1>(result, x, y);
			board_increment::get_point_list_impl<_Fir::value | _Sec::value | _Thi::value | _Fou::value | 0x2>(result, x, y);
			board_increment::get_point_list_impl<_Fir::value | _Sec::value | _Thi::value | _Fou::value | 0x4>(result, x, y);
			board_increment::get_point_list_impl<_Fir::value | _Sec::value | _Thi::value | _Fou::value | 0x8>(result, x, y);
			return std::move(result);
		}

		template<unsigned char _Flg>
		static void get_point_list_impl(std::vector<point>& base, const unsigned char x, const unsigned char y)
		{
		}

		template<>
		static void get_point_list_impl<0x0>(std::vector<point>& base, const unsigned char x, const unsigned char y)
		{
			return ;
		}

		template<>
		static void get_point_list_impl<0x1>(std::vector<point>& base, const unsigned char x, const unsigned char y)
		{
			for (unsigned char i = 0; i < 8; ++i) {
				if (i != y) {
					base.push_back(point(x, i));
				}
			}
		}

		template<>
		static void get_point_list_impl<0x2>(std::vector<point>& base, const unsigned char x, const unsigned char y)
		{
			for (unsigned char i = 0; i < 8; ++i) {
				if (i != x) {
					base.push_back(point(i, y));
				}
			}
		}

		template<>
		static void get_point_list_impl<0x4>(std::vector<point>& base, const unsigned char x, const unsigned char y)
		{
			if (x >= y) {
				unsigned char ix = x - y;
				unsigned char iy = 0;
				for (; ix < 8; ++ix, ++iy) {
					if (iy != y) {
						base.push_back(point(ix, iy));
					}
				}
			}
			else {
				unsigned char ix = 0;
				unsigned char iy = y - x;
				for (; iy < 8; ++ix, ++iy) {
					if (ix != x) {
						base.push_back(point(ix, iy));
					}
				}
			}
		}

		template<>
		static void get_point_list_impl<0x8>(std::vector<point>& base, const unsigned char x, const unsigned char y)
		{
			if (x + y <= 7) {
				unsigned char ix = x + y;
				unsigned char iy = 0;
				for (; ix >= 0; --ix, ++iy) {
					if (iy != y) {
						base.push_back(point(ix, iy));
					}
				}
			}
			else {
				unsigned char ix = 7;
				unsigned char iy = x + y;
				for (; iy < 8; --ix, ++iy) {
					if (iy != y) {
						base.push_back(point(ix, iy));
					}
				}
			}
		}

	};
}