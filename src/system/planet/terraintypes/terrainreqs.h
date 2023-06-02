#ifndef TERRAINREQ_H
#define TERRAINREQ_H
typedef struct TerrainReq {
  std::string type;
  std::string comp;
  int count;

	constexpr TerrainReq(std::string n, std::string c, int co) noexcept
		: type{ n }, comp{ c }, count{ co } {}
};
#endif