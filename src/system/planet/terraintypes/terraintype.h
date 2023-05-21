#ifndef TERRAINTYPE_H
#define TERRAINTYPE_H
#include "../../utils/rgb.h"
typedef struct TerrainType
{
	std::string name;
	double height;
	RGB color;

	 TerrainType(std::string _n, double _h, RGB _r) noexcept
		: name{ _n }, height{ _h }, color{ _r } {}
};
#endif