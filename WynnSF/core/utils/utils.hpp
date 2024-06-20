#pragma once
#include <utility>


namespace Core {
	namespace Utils {
		float fisqrt(float num);
		/*
		constexpr inline auto enum_range = [](auto front, auto back) {
			return std::views::iota(std::to_underlying(front), std::to_underlying(back) + 1)
				| std::views::transform([](auto e) { return decltype(front)(e); });
			};
		
		*/
		
	}
}