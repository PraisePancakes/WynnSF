#pragma once
#include "../utils/utils.hpp"
#include <cmath>
namespace Core {
	namespace Physics {
		class Vec2 {
		public:
			float x = 0;
			float y = 0;

			Vec2(float x, float y) {
				this->x = x;
				this->y = y;
			};

			Vec2() {};

			Vec2 operator+(Vec2 rhs) {
				return Vec2(rhs.x + this->x, rhs.y + this->y);
			};

			Vec2 operator-(Vec2 rhs) {
				return Vec2(rhs.x - this->x, rhs.y - this->y);
			};

			Vec2 operator/(Vec2 rhs) {
				return Vec2(rhs.x / this->x, rhs.y / this->y);
			};

			Vec2 operator*(Vec2 rhs) {
				return Vec2(rhs.x * this->x, rhs.y * this->y);
			};

			void operator+=(Vec2 rhs) {
				this->x += rhs.x;
				this->y += rhs.y;
			}

			void operator-=(Vec2 rhs) {
				this->x -= rhs.x;
				this->y -= rhs.y;
			}

			void operator/=(Vec2 rhs) {
				this->x /= rhs.x;
				this->y /= rhs.y;
			}

			void operator*=(Vec2 rhs) {
				this->x *= rhs.x;
				this->y *= rhs.y;
			}

			bool operator==(Vec2 rhs) {
				return (this->x == rhs.x && this->y == rhs.y);
			}

			bool operator!=(Vec2 rhs) {
				return (this->x != rhs.x || this->y != rhs.y);
			}

			void Normalize() {
				float invlength = Core::Utils::fisqrt(((x * x) + (y *y))); //shout out quake
				this->x *=  invlength;
				this->y *=  invlength;
			};



		};
	}
}