#pragma once


namespace Core {
	namespace Utils {
		float fisqrt(float num) {
			//QUAKE GODS HAVE SPOKEN

			long i;
			float x2, y;
			const float threehalfs = 1.5F;

			x2 = num * 0.5F;
			y = num;
			i = *(long*)&y;
			i = 0x5f3759df - (i >> 1);
			y = *(float*)&i;
			y = y * (threehalfs - (x2 * y * y));


			return y;
		}
	}
}