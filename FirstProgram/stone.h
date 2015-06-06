#pragma once

namespace oth
{
	struct none
	{
		struct get_reverse
		{
			typedef none type;
		};
	};

	struct white;

	struct black
	{
		struct get_reverse
		{
			typedef white type;
		};
	};

	struct white
	{
		struct get_reverse
		{
			typedef black type;
		};
	};

	typedef unsigned char stone;
	const stone NONE = 0;
	const stone BLACK = 1;
	const stone WHITE = 2;

	struct stone_utility
	{
		static stone get_reverse(const stone stn)
		{
			if (stn == NONE)
			{
				return NONE;
			}
			else
			{
				return (BLACK + WHITE) - stn;
			}
		}
	};

	
}
