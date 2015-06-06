#pragma once

namespace oth
{
	namespace vector
	{
		struct nothing { static const char value = 0; };
		struct up { static const char value = 1; };
		struct right { static const char value = 1; };
		struct down { static const char value = -1; };
		struct left { static const char value = -1; };
	}

	namespace line
	{
		struct nothing {};
		struct vertical {};
		struct horizontal {};
		struct left_cross {};
		struct right_cross {};
	}
}
