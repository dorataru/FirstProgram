#pragma once
#include <iostream>
#include "base.h"
#include "stone.h"
#include <vector>

namespace oth
{
	class board
	{
	private:
		unsigned long long _black;
		unsigned long long _white;

	private:
		template<unsigned char _X, unsigned char _Y>
		struct get_index
		{
			static const unsigned char value = _X + (_Y * 8);
		};

		static unsigned char get_index_d(const unsigned char x, const unsigned char y)
		{
			return x + (y * 8);
		}

		template<unsigned char _X, unsigned char _Y>
		struct get_bit
		{
			static const unsigned long long value = 0x1ull << board::get_index<_X, _Y>::value;
		};

		static unsigned long long get_bit_d(const unsigned char x, const unsigned char y)
		{
			return 0x1ull << board::get_index_d(x, y);
		}

	public:
		static void print_mark(const unsigned char x, const unsigned char y)
		{
			for (unsigned char i = 0; i < 8; ++i) {
				for (unsigned char j = 0; j < 8; ++j) {
					if (j == x) {
						std::cout << "~";
					}
					else if (i == y) {
						std::cout << "~";
					}
					else if (x + y == i + j) {
						std::cout << "~";
					}
					else if (x - y == j - i) {
						std::cout << "~";
					}
					else {
						std::cout << " ";
					}
				}
				std::cout << std::endl;
			}
			std::cout << std::endl << std::endl;
		}

		template<class _Ver, class _Hol, class _Lcr, class _Rcr>
		struct line_bundler
		{
			typedef _Ver vertical;
			typedef _Hol horizontal;
			typedef _Lcr left_cross;
			typedef _Rcr right_cross;

			template<class _Lin>
			struct add
			{
			};

			template<>
			struct add<line::nothing>
			{
				typedef line_bundler<_Ver, _Hol, _Lcr, _Rcr> type;
			};

			template<>
			struct add<line::vertical>
			{
				typedef line_bundler<line::vertical, _Hol, _Lcr, _Rcr> type;
			};

			template<>
			struct add<line::horizontal>
			{
				typedef line_bundler<_Ver, line::horizontal, _Lcr, _Rcr> type;
			};

			template<>
			struct add<line::left_cross>
			{
				typedef line_bundler<_Ver, _Hol, line::left_cross, _Rcr> type;
			};

			template<>
			struct add<line::right_cross>
			{
				typedef line_bundler<_Ver, _Hol, _Lcr, line::right_cross> type;
			};
			
		};


	public:
		board(const unsigned long long black = 0ull, const unsigned long long white = 0ull) :
			_black(black),
			_white(white)
		{}

		board(const board& other) :
			_black(other._black),
			_white(other._white)
		{}

	public:
		template<unsigned char _X, unsigned char _Y>
		struct is_valid_position
		{
			static const bool value = _X >= 0 && _X < 8 && _Y >= 0 && _Y < 8;
		};
		
		static bool is_valid_position_d(const unsigned char x, const unsigned char y)
		{
			return x >= 0 && x < 8 && y >= 0 && y < 8;
		}

		template<unsigned char _X, unsigned char _Y>
		stone get() const
		{
			if (this->_black & board::get_bit<_X, _Y>::value) {
				return BLACK;
			}
			else if (this->_white & board::get_bit<_X, _Y>::value) {
				return WHITE;
			}
			else
			{
				return NONE;
			}
		}

		stone get_d(const unsigned char x, const unsigned char y) const
		{
			const unsigned long long bit = board::get_bit_d(x, y);
			if (this->_black & bit) {
				return BLACK;
			}
			else if (this->_white & bit) {
				return WHITE;
			}
			else {
				return NONE;
			}
		}

		template<unsigned char _X, unsigned char _Y, class _Stn>
		void set(
			typename std::enable_if<
				std::is_same<_Stn, none>::value
			>::type* = 0)
		{
			this->_black &= ~board::get_bit<_X, _Y>::value;
			this->_white &= ~board::get_bit<_X, _Y>::value;
		}

		template<unsigned char _X, unsigned char _Y, class _Stn>
		void set(
			typename std::enable_if<
				std::is_same<_Stn, black>::value
			>::type* = 0)
		{
			this->_black |= board::get_bit<_X, _Y>::value;
			this->_white &= ~board::get_bit<_X, _Y>::value;
		}

		template<unsigned char _X, unsigned char _Y, class _Stn>
		void set(
			typename std::enable_if<
				std::is_same<_Stn, white>::value
			>::type* = 0)
		{
			this->_black &= ~board::get_bit<_X, _Y>::value;
			this->_white |= board::get_bit<_X, _Y>::value;
		}

		/* */
		template<class _Stn>
		void set_d(
			const unsigned char x,
			const unsigned char y,
			typename std::enable_if<
				std::is_same<_Stn, none>::value
			>::type* = 0)
		{
			const unsigned long long bit = board::get_bit_d(x, y);
			this->_black &= ~bit;
			this->_white &= ~bit;
		}

		template<class _Stn>
		void set_d(
			const unsigned char x,
			const unsigned char y,
			typename std::enable_if<
				std::is_same<_Stn, black>::value
			>::type* = 0)
		{
			const unsigned long long bit = board::get_bit_d(x, y);
			this->_black |= bit;
			this->_white &= ~bit;
		}

		template<class _Stn>
		void set_d(
			const unsigned char x,
			const unsigned char y,
			typename std::enable_if<
				std::is_same<_Stn, white>::value
			>::type* = 0)
		{
			const unsigned long long bit = board::get_bit_d(x, y);
			this->_black &= ~bit;
			this->_white |= bit;
		}
		/* */

		/* */
		void set_d(const unsigned char x, const unsigned char y, const stone stn)
		{
			const unsigned long long bit = board::get_bit_d(x, y);
			if (stn == BLACK) {
				this->_black |= bit;
				this->_white &= ~bit;
			}
			else if (stn == WHITE) {
				this->_black &= ~bit;
				this->_white |= bit;
			}
			else
			{
				this->_black &= ~bit;
				this->_white &= ~bit;
			}
		}
		/* */

		template<class _Stn>
		unsigned long long get_bitline(
			typename std::enable_if<
				std::is_same<_Stn, black>::value
			>::type* = 0) const
		{
			return this->_black;
		}

		template<class _Stn>
		unsigned long long get_bitline(
			typename std::enable_if<
				std::is_same<_Stn, white>::value
			>::type* = 0) const
		{
			return this->_white;
		}

		board& operator=(const board& other)
		{
			this->_black = other._black;
			this->_white = other._white;
			return *this;
		}

		bool operator==(const board& other) const
		{
			return this->_black == other._black && this->_white == other._white;
		}

		bool operator!=(const board& other) const
		{
			return !this->operator==(other);
		}

		void print() const
		{
			for (unsigned char y = 0; y < 8; ++y) {
				for (unsigned char x = 0; x < 8; ++x) {
					const stone stn = this->get_d(x, y);
					if (stn == BLACK) {
						std::cout << "›";
					}
					else if (stn == WHITE) {
						std::cout << "œ";
					}
					else {
						std::cout << " ";
					}
				}
				std::cout << std::endl;
			}
			std::cout << std::endl << std::endl;
		}



	};
}
