#pragma once

namespace Math {
	inline float SmoothExponential(float current, float target, float alpha) {
		return alpha * target + (1 - alpha) * current;
	}
}