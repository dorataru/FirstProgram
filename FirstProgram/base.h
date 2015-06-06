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
		struct nothing { static const unsigned char value = 0x0; };
		struct vertical { static const unsigned char value = 0x1; };
		struct horizontal { static const unsigned char value = 0x2; };
		struct left_cross { static const unsigned char value = 0x4; };
		struct right_cross { static const unsigned char value = 0x8; };
	}
}
