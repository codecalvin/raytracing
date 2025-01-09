#ifndef COLOR_H
#define COLOR_H
//==============================================================================================
// Originally written in 2020 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include "interval.h"
#include "vec3.h"

using color = vec3;


inline double linear_to_gamma(double linear_component)
{
	if (linear_component > 0)
		return std::sqrt(linear_component);

	return 0;
}

inline color linear_to_gamma(const color& pixel_color)
{
	return {
		linear_to_gamma(pixel_color[0]),
linear_to_gamma(pixel_color[1]),
linear_to_gamma(pixel_color[2])
	};
}


inline void convert_color(const color& pixel_color, uint8_t* output) {
	auto gamma_color = linear_to_gamma(pixel_color);

	// Translate the [0,1] component values to the byte range [0,255].
	static const interval intensity(0.000, 0.999);
	output[0] = uint8_t(256 * intensity.clamp(gamma_color.x()));
	output[1] = uint8_t(256 * intensity.clamp(gamma_color.y()));
	output[2] = uint8_t(256 * intensity.clamp(gamma_color.z()));
}

void write_color(std::ostream& out, const color& pixel_color) {
	// Write out the pixel color components.
	uint8_t rgb[3];
	convert_color(pixel_color, rgb);
	out << rgb[0] << ' ' << rgb[1] << ' ' << rgb[2] << '\n';
}


#endif
