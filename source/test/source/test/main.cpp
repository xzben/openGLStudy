#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include "utils/Utils.h"

namespace OGS_OLD {
	struct  Vec3
	{
		union
		{
			struct
			{
				float x, y, z;
			};
			struct
			{
				float r, g, b;
			};
		};
	};


	using Position = Vec3;
	using Rotation = Vec3;
	using Scale = Vec3;

	void test()
	{
		std::cout << typeid(float).name() << std::endl;

		std::cout << typeid(Position).name() << std::endl;
		std::cout << typeid(Rotation).name() << std::endl;
		std::cout << typeid(Scale).name() << std::endl;
	}
}

int main()
{
	float values[16];


	std::cout << sizeof(values) << std::endl;
	return 0;
}