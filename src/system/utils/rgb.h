#ifndef RGB_H
#define RGB_H
typedef struct RGB
{
	double r = 0.0;
	double g = 0.0;
	double b = 0.0;
	constexpr RGB() = default;
	explicit constexpr RGB(double _rgb) noexcept
		: r{ _rgb }, g{ _rgb }, b{ _rgb } {}
	constexpr RGB(double _r, double _g, double _b) noexcept
		: r{ _r }, g{ _g }, b{ _b } {}
};
#endif